//
// Created by dim on 24/03/2021.
//

#include "AsteroidWaveScript.h"
#include "../entities/AsteroidEntity.h"
#include "../../core/Game.h"

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
    Vector3 playerPos = playerRef->getPosition();

    // Spawn initial test asteroid
    Entity* ast = AsteroidEntity::getEntity(this);
    AsteroidScript* asteroidScript = dynamic_cast<AsteroidScript*>(ast->getComponentOfType(ComponentType::CScript));

    ast->setPosition(getPositionOutOfArena(asteroidScript->getRadius()));

    RigidbodyComponent* rb = dynamic_cast<RigidbodyComponent*>(ast->getComponentOfType(ComponentType::CRigidbody));

    // Add force to move to player
    rb->addForce(VectorUtil::Normalize(playerPos - ast->getPosition()) * asteroidScript->getSpeed());

    // Set rotation to either left/right and to config values
    float rotVel = getRandomNumber(ASTEROID_MIN_ROTATION, ASTEROID_MAX_ROTATION);
    rb->setForceRot(rand() % 2 ? rotVel : -rotVel);

    Game::getEngine()->getScene()->addEntity(ast);

    asteroids.emplace(ast);
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
