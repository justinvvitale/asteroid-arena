//
// Created by dim on 24/03/2021.
//

#include "AsteroidWaveScript.h"
#include "../entities/AsteroidEntity.h"
#include "../../core/Game.h"

void AsteroidWaveScript::start() {
    launchRadius = (float) sqrt(pow(ARENA_WIDTH / 2, 2) + pow(ARENA_HEIGHT / 2, 2));
    playerRef = Game::getEntity(EntityTag::Player);

    if (DEBUG_DRAW_LAUNCH_CIRCLE) {
        MeshComponent* meshComponent = new MeshComponent();
        meshComponent->setMesh(MeshHelper::getCircleMesh(launchRadius, DEBUG_DRAW_LAUNCH_CIRCLE_COLOUR));
        this->getEntity()->addComponent(meshComponent);
    }

}

void AsteroidWaveScript::update() {
    // Spawning
    if (Game::tick % ASTEROID_SPAWN_RATE == 0 && asteroids.size() < ASTEROID_MAX) {
        spawnAsteroid();
    }

    // Cleanup when off screen
    if (Game::tick % ASTEROID_CLEAR_RATE == 0) {

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

    Game::getEngine()->getScene()->addEntity(ast);

    asteroids.emplace(ast);
}

void AsteroidWaveScript::despawnAsteroid(Entity* asteroid) {
    if (asteroids.find(asteroid) != asteroids.end()) {
        Game::getEngine()->getScene()->removeEntity(asteroid);
        Game::queueEntityCleanup(asteroid);
        asteroids.erase(asteroid);
    }
}

