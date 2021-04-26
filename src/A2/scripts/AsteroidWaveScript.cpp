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

    if (Game::state != GameState::Playing) return;

    int elapsed = Game::elapsed;

    // Spawning
    if (scoreScript->isCD) {
        if (elapsed - cdStartTime >= ASTEROID_WAVE_CD) {
            scoreScript->wave++;
            scoreScript->isCD = false;
            asteroidSpawnAmount += ASTEROID_SPAWN_INCREMENT;

            // Spawn wave
            for (int i = 0; i < asteroidSpawnAmount; i++) {
                spawnAsteroid();
            }
        }
    } else if (asteroids.empty()) {
        cdStartTime = elapsed;
        scoreScript->isCD = true;
    }

    // Cleanup when off screen
    if (elapsed - lastClearTime >= ASTEROID_CLEAR_RATE) {

        std::set<Entity*>::iterator entityIter = asteroids.begin();
        while (entityIter != asteroids.end()) {
            Entity* ast = *entityIter;

            float dist = VectorUtil::Distance(ast->getPosition(), Vector3::zero());

            // If distance greater than launch radius and max radius and some buffer, then destroy
            if (dist > launchRadius + ASTEROID_MAX_RADIUS + 500) {
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
    float angle = (float)(rand() * PI * 2);
    return {cos(angle) * (launchRadius + payloadSize), sin(angle) * (launchRadius + payloadSize), 0};
}

void AsteroidWaveScript::spawnAsteroid() {
    // Fetch and calculate variables
    float speed = getRandomNumber(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
    float radius = ASTEROID_MIN_RADIUS + (float)(rand() % static_cast<int>(ASTEROID_MAX_RADIUS - ASTEROID_MIN_RADIUS + 1));
    Vector3 position = getPositionOutOfArena(radius); // Set rotation to either left/right and to config values
    float rotation = getRandomNumber(ASTEROID_MIN_ROTATION, ASTEROID_MAX_ROTATION);
    Vector3 force = VectorUtil::Normalize(playerRef->getPosition() - position) * speed;

    // Spawn configured asteroid
    spawnAsteroid(ASTEROID_HEALTH_MULTIPLIER * radius, position, speed, radius, rand() % 2 ? rotation : -rotation,
                  force, true);
}

void AsteroidWaveScript::spawnAsteroid(float health, Vector3 position, float speed, float radius, float rotation,
                                       Vector3 force, bool canSplit) {
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

void AsteroidWaveScript::splitAsteroid(Entity* asteroid, bool scored) {
    AsteroidScript* script = dynamic_cast<AsteroidScript*>(asteroid->getComponentOfType(ComponentType::CScript));
    RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(asteroid->getComponentOfType(
            ComponentType::CRigidbody));

    float brokenRadius = script->getRadius() / 2;
    float speed = script->getSpeed() / 2;


    // Original 45 degree velocity code,
//    Vector3 direction = VectorUtil::Normalize(rigid->getVelocity());
//    float t = 45 * (PI / 180);
//    Vector3 forceL =
//            Vector3(direction.x * cos(t) - direction.y * sin(t), direction.x * sin(t) + direction.y * cos(t), 0) *
//            speed;
//    Vector3 forceR =
//            Vector3(direction.x * cos(-t) - direction.y * sin(-t), direction.x * sin(-t) + direction.y * cos(-t), 0) *
//            speed;

    // Original LEFT/RIGHT split
//    Vector3 posL = asteroid->getOffset() + Vector3(brokenRadius + ASTEROID_RADIUS_VARIATION_RANGE, 0, 0);
//    Vector3 posR = asteroid->getOffset() - Vector3(brokenRadius + ASTEROID_RADIUS_VARIATION_RANGE, 0, 0);

    srand((unsigned) time(nullptr));
    float angle = getRandomNumber(0, 360);
    Vector3 posL = Vector3(cos(angle) * (brokenRadius + 2), sin(angle) * (brokenRadius + 2), 0);
    Vector3 posR = posL.opposite();

    Vector3 astPos = asteroid->getWorldPosition();
    posL = posL + astPos;
    posR = posR + astPos;


    Vector3 playerPos = asteroid->getWorldPosition();
    Vector3 forceL = VectorUtil::Normalize(posL - playerPos) * speed;
    Vector3 forceR  = VectorUtil::Normalize(posR - playerPos) * speed;

    spawnAsteroid(ASTEROID_HEALTH_MULTIPLIER * brokenRadius,
                  posL , speed,
                  brokenRadius, rigid->getSpin() * 1.2f, forceL, false);
    spawnAsteroid(ASTEROID_HEALTH_MULTIPLIER * brokenRadius,
                  posR, speed,
                  brokenRadius, rigid->getSpin() * 1.2f, forceR, false);


    destroyAsteroid(asteroid, scored);
}

void AsteroidWaveScript::destroyAsteroid(Entity* asteroid, bool scored) {
    // Particles for destroying
    for (int i = 0; i < ASTEROID_PARTICLE_DESTROY_COUNT; i++) {
        Vector3 vel = Vector3(
                (float) getRandomNumber(-ASTEROID_PARTICLE_VELOCITY_RANGE, ASTEROID_PARTICLE_VELOCITY_RANGE),
                (float) getRandomNumber(-ASTEROID_PARTICLE_VELOCITY_RANGE, ASTEROID_PARTICLE_VELOCITY_RANGE), 0);

        ParticleSystem::emit(new Particle(vel, (float)ASTEROID_PARTICLE_LIFESPAN +
                                                               (float)getRandomNumber(-ASTEROID_PARTICLE_LIFESPAN_VARIATION,
                                                               ASTEROID_PARTICLE_LIFESPAN_VARIATION), 1, 4,
                                          MeshHelper::getHexagonMesh(3, ASTEROID_COLOUR)), asteroid->getPosition());
    }

    if (scored) {
        this->scoreScript->addScore(SCORE_AMOUNT_ASTEROID_KILL);
    }

    if (asteroids.find(asteroid) != asteroids.end()) {
        asteroid->destroy();
        asteroids.erase(asteroid);
    }
}

