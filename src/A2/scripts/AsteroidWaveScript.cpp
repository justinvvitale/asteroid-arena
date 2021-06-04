//
// Created by dim on 24/03/2021.
//

#include "AsteroidWaveScript.h"
#include "../entities/AsteroidEntity.h"
#include "../../core/Game.h"
#include "../GameState.h"
#include "../../core/ecs/components/ParticleEmitterComponent.h"
#include "../../core/ecs/systems/ParticleSystem.h"
#include "../../core/audio/AudioPlayer.h"

void AsteroidWaveScript::start() {
    scoreScript = dynamic_cast<ScoreScript*>(Game::getEntity("score")->getComponentOfType(ComponentType::CScript));
    shipRef = Game::getEntity("player");
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
            AudioPlayer::playOnce("wavestart");

            // Spawn wave
            for (int i = 0; i < asteroidSpawnAmount; i++) {
                spawnAsteroid();
            }
        }
    } else if (asteroids.empty()) {
        cdStartTime = elapsed;
        scoreScript->isCD = true;

        if(scoreScript->wave > 0){
            AudioPlayer::playOnce("wavefinish");
        }
    }

    // Cleanup when off screen
    if (elapsed - lastClearTime >= ASTEROID_CLEAR_RATE) {

        std::set<Entity*>::iterator entityIter = asteroids.begin();
        while (entityIter != asteroids.end()) {
            Entity* ast = *entityIter;

            AsteroidScript* astScript = dynamic_cast<AsteroidScript*>(ast->getComponentOfType(CScript));

            // If not in arena cube and primed
            if (astScript->isPrimed() && !isInsideCube(ast->getPosition(), ARENA_SIZE, astScript->getRadius())) {
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

Vector3 AsteroidWaveScript::getPositionOutOfArena(float payloadSize) {
    float halfArena = ARENA_SIZE/2;

    // Brute force, performant enough for assignment but ideally I would calculate a point outside of cuboid area using actual math :?
    Vector3 result = Vector3(0,0,0);
    while(isInsideCube(result, ARENA_SIZE, payloadSize)){
        float wiggleRoom = payloadSize + 500;
        float range = wiggleRoom + halfArena;
        result.x = getRandomNumber(-range,range);
        result.y = getRandomNumber(-range,range);
        result.z = getRandomNumber(-range,range);
    }

    return result;
}

void AsteroidWaveScript::spawnAsteroid() {
    // Fetch and calculate variables
    float speed = getRandomNumber(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
    float radius = ASTEROID_MIN_RADIUS + (float)(rand() % static_cast<int>(ASTEROID_MAX_RADIUS - ASTEROID_MIN_RADIUS + 1));
    Vector3 position = getPositionOutOfArena(radius); // Set rotation to either left/right and to config values
    Vector3 rotation = Vector3(getRandomNumber(ASTEROID_MIN_ROTATION, ASTEROID_MAX_ROTATION), getRandomNumber(ASTEROID_MIN_ROTATION, ASTEROID_MAX_ROTATION), getRandomNumber(ASTEROID_MIN_ROTATION, ASTEROID_MAX_ROTATION));
    Vector3 force = VectorUtil::Normalize(shipRef->getPosition() - position) * speed;

    // Spawn configured asteroid
    spawnAsteroid(ASTEROID_HEALTH_MULTIPLIER * radius, position, speed, radius, rand() % 2 ? rotation : rotation.opposite(),
                  force, true);
}

void AsteroidWaveScript::spawnAsteroid(float health, Vector3 position, float speed, float radius, Vector3 rotation,
                                       Vector3 force, bool canSplit) {
    // Create entity and add script
    Entity* ast = AsteroidEntity::getEntity();
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

// Still works in 3D somehow, lol why not.
void AsteroidWaveScript::splitAsteroid(Entity* asteroid, bool scored) {
    AsteroidScript* script = dynamic_cast<AsteroidScript*>(asteroid->getComponentOfType(ComponentType::CScript));
    RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(asteroid->getComponentOfType(
            ComponentType::CRigidbody));

    float brokenRadius = script->getRadius() / 2;
    float speed = script->getSpeed() / 2;

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
                (float) getRandomNumber(-ASTEROID_PARTICLE_VELOCITY_RANGE, ASTEROID_PARTICLE_VELOCITY_RANGE),
                (float) getRandomNumber(-ASTEROID_PARTICLE_VELOCITY_RANGE, ASTEROID_PARTICLE_VELOCITY_RANGE)
                );

        ParticleSystem::emit(new Particle(vel, (float)ASTEROID_PARTICLE_LIFESPAN +
                                                               (float)getRandomNumber(-ASTEROID_PARTICLE_LIFESPAN_VARIATION,
                                                               ASTEROID_PARTICLE_LIFESPAN_VARIATION), 5, 20, "chunk"),
                             asteroid->getPosition());
    }

    if (scored) {
        this->scoreScript->addScore(SCORE_AMOUNT_ASTEROID_KILL);
    }

    if (asteroids.find(asteroid) != asteroids.end()) {
        asteroid->destroy();
        asteroids.erase(asteroid);
    }
}

