//
// Created by dim on 24/03/2021.
//

#include "AsteroidWaveScript.h"
#include "../entities/AsteroidEntity.h"
#include "../../core/Game.h"
#include "../GameState.h"

void AsteroidWaveScript::start() {
    scoreScript = dynamic_cast<ScoreScript*>(Game::getEntity("score")->getComponentOfType(ComponentType::CScript));
    launchRadius = (float) sqrt(pow(ARENA_WIDTH / 2, 2) + pow(ARENA_HEIGHT / 2, 2));
    playerRef = Game::getEntity("player");

    if (DEBUG_DRAW_LAUNCH_CIRCLE) {
        MeshComponent* meshComponent = new MeshComponent();
        meshComponent->setMesh(MeshHelper::getCircleMesh(launchRadius, DEBUG_DRAW_LAUNCH_CIRCLE_COLOUR));
        this->getEntity()->addComponent(meshComponent);
    }

}

void AsteroidWaveScript::update() {

    if(Game::state != GameState::Playing) return;

    // Spawning
    int elapsed = Game::elapsed;
    if (elapsed - lastSpawnTime >= ASTEROID_SPAWN_RATE && asteroids.size() < ASTEROID_MAX) {
        spawnAsteroid();
        lastSpawnTime = elapsed;
    }

    // Cleanup when off screen
    if (elapsed - lastClearTime >= ASTEROID_CLEAR_RATE) {

        std::set<Entity*>::iterator entityIter = asteroids.begin();
        while (entityIter != asteroids.end()) {
            Entity* ast = *entityIter;

            float dist = VectorUtil::Distance(ast->getPosition(), Vector3::zero());

            if (dist > launchRadius + ASTEROID_MAX_RADIUS) {
                Game::getEngine()->getScene()->removeEntity(ast);
                Game::queueEntityCleanup(ast);
                asteroids.erase(entityIter++);
            } else {
                ++entityIter;
            }
        }

        lastClearTime = elapsed;
    }

}

Vector3 AsteroidWaveScript::getPositionOutOfArena(float payloadSize) const {
    float angle = rand() * PI * 2;
    return {cos(angle) * (launchRadius + payloadSize), sin(angle) * (launchRadius + payloadSize), 0};
}

void AsteroidWaveScript::spawnAsteroid() {
    // Fetch and calculate variables
    float speed = getRandomNumber(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
    float radius = ASTEROID_MIN_RADIUS + (rand() % static_cast<int>(ASTEROID_MAX_RADIUS - ASTEROID_MIN_RADIUS + 1));
    Vector3 position = getPositionOutOfArena(radius); // Set rotation to either left/right and to config values
    float rotation = getRandomNumber(ASTEROID_MIN_ROTATION, ASTEROID_MAX_ROTATION);
    Vector3 force = VectorUtil::Normalize(playerRef->getPosition() - position) * speed;

    // Spawn configured asteroid
    spawnAsteroid(ASTEROID_HEALTH, position, speed, radius, rand() % 2 ? rotation : -rotation, force, true);
}

void AsteroidWaveScript::spawnAsteroid(float health, Vector3 position, float speed, float radius, float rotation, Vector3 force, bool canSplit) {
    // Create entity and add script
    Entity* ast = AsteroidEntity::getEntity(radius);
    AsteroidScript* asteroidScript = new AsteroidScript(this, health, radius, speed, canSplit);

    ast->addComponent(asteroidScript);

    ast->setPosition(position);

    RigidbodyComponent* rb = dynamic_cast<RigidbodyComponent*>(ast->getComponentOfType(ComponentType::CRigidbody));

    // Add force to move to player
    rb->addForce(force);
    rb->setForceRot(rotation);

    Game::getEngine()->getScene()->addEntity(ast);

    asteroids.emplace(ast);
}

void AsteroidWaveScript::splitAsteroid(Entity* asteroid) {
    AsteroidScript* script = dynamic_cast<AsteroidScript*>(asteroid->getComponentOfType(ComponentType::CScript));
    spawnAsteroid(1, asteroid->getPosition(), 0, script->getRadius()/2, 0, Vector3::zero(), false);


    destroyAsteroid(asteroid, true);
}

void AsteroidWaveScript::destroyAsteroid(Entity* asteroid, bool scored) {
    if (asteroids.find(asteroid) != asteroids.end()) {
        asteroid->destroy();
        asteroids.erase(asteroid);
    }

    if(scored){
        this->scoreScript->addScore(SCORE_AMOUNT_ASTEROID_KILL);
    }
}




