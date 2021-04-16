//
// Created by dim on 24/03/2021.
//

#include "AsteroidWaveScript.h"
#include "../entities/AsteroidEntity.h"
#include "../../core/Game.h"
#include "../GameState.h"
#include "../../core/ecs/components/ParticleEmitterComponent.h"
#include "../../core/ecs/systems/ParticleSystem.h"

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

    int elapsed = Game::elapsed;

    // Spawning
    if(isCD) {
        if (elapsed - cdStartTime >= ASTEROID_WAVE_CD) {
            isCD = false;
            asteroidSpawnAmount += ASTEROID_SPAWN_INCREMENT;

            // Spawn wave
            for(int i = 0; i < asteroidSpawnAmount; i++){
                spawnAsteroid();
            }
        }
    }else if(asteroids.empty()){
            cdStartTime = elapsed;
            wave++;
            std::cout << "WAVE" << std::endl;
            isCD = true;
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
    spawnAsteroid(ASTEROID_HEALTH_MULTIPLIER * radius, position, speed, radius, rand() % 2 ? rotation : -rotation, force, true);
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
    rb->setSpin(rotation);

    Game::getEngine()->getScene()->addEntity(ast);

    asteroids.emplace(ast);
}

void AsteroidWaveScript::splitAsteroid(Entity* asteroid) {
    AsteroidScript* script = dynamic_cast<AsteroidScript*>(asteroid->getComponentOfType(ComponentType::CScript));
    RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(asteroid->getComponentOfType(ComponentType::CRigidbody));

    float brokenRadius = script->getRadius()/2;
    float speed = script->getSpeed()/2;
    Vector3 direction = VectorUtil::Normalize(rigid->getVelocity());

    float t = 45 * (PI/180);
    Vector3 forceL = Vector3(direction.x * cos(t) - direction.y * sin(t), direction.x * sin(t) + direction.y * cos(t), 0) * speed;
    Vector3 forceR = Vector3(direction.x * cos(-t) - direction.y * sin(-t), direction.x * sin(-t) + direction.y * cos(-t), 0) * speed;


    spawnAsteroid(1, asteroid->getPosition() + Vector3(brokenRadius + ASTEROID_RADIUS_VARIATION_RANGE,0,0), speed, brokenRadius, 0, forceL, false);
    spawnAsteroid(1, asteroid->getPosition() - Vector3(brokenRadius + ASTEROID_RADIUS_VARIATION_RANGE,0,0), speed, brokenRadius, 0, forceR, false);


    destroyAsteroid(asteroid, true);
}

void AsteroidWaveScript::destroyAsteroid(Entity* asteroid, bool scored) {
    if(scored){
        for(int i = 0; i < 50; i++) {
            Vector3 vel = Vector3(randomSign((float) getRandomNumber(0, 400)), randomSign((float) getRandomNumber(0, 400)), 0);

            ParticleSystem::emit(new Particle(vel, 1000, 1, 4, MeshHelper::getHexagonMesh(3, ASTEROID_COLOUR)), asteroid->getPosition());
        }
        this->scoreScript->addScore(SCORE_AMOUNT_ASTEROID_KILL);
    }

    if (asteroids.find(asteroid) != asteroids.end()) {
        asteroid->destroy();
        asteroids.erase(asteroid);
    }
}




