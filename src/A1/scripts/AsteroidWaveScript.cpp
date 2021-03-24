//
// Created by dim on 24/03/2021.
//

#include "AsteroidWaveScript.h"
#include "../entities/AsteroidEntity.h"
#include "../../core/Game.h"

void AsteroidWaveScript::start() {
    launchRadius = (float)sqrt(pow(ARENA_WIDTH/2,2) + pow(ARENA_HEIGHT/2,2));
    playerRef = Game::getEntity(EntityTag::Player);

    if(DEBUG_DRAW_LAUNCH_CIRCLE){
        MeshComponent* meshComponent = new MeshComponent();
        meshComponent->setMesh(MeshHelper::getCircleMesh(launchRadius, DEBUG_DRAW_LAUNCH_CIRCLE_COLOUR));
        this->getParent()->addComponent(meshComponent);
    }

}

void AsteroidWaveScript::update() {
    // Spawning
    if(Game::tick % ASTEROID_SPAWN_RATE == 0 && asteroids.size() < ASTEROID_MAX){
        std::cout << asteroids.size() << std::endl;
        spawnAsteroid();
    }

    // Cleanup when off screen
    if(Game::tick % ASTEROID_CLEAR_RATE == 0){

        std::list<Entity*>::iterator entityIter = asteroids.begin();
        while (entityIter != asteroids.end()){
            Entity* ast = *entityIter;

            float dist = VectorUtil::Distance(ast->getPosition(), Vector3::zero());

            if(dist > launchRadius + ASTEROID_MAX_RADIUS){
                Game::getEngine()->getScene()->removeEntity(ast);
                Game::queueCleanup(ast);
                asteroids.erase(entityIter++);
            }else{
                ++entityIter;
            }
        }
    }
}

Vector3 AsteroidWaveScript::getPositionOutOfArena(float payloadSize) const {
    float angle = rand() * 3.14 * 2;
    return {cos(angle) * (launchRadius + payloadSize), sin(angle) * (launchRadius + payloadSize), 0};
}

void AsteroidWaveScript::spawnAsteroid() {
    Vector3 playerPos = playerRef->getPosition();

    // Spawn initial test asteroid
    Entity* ast = AsteroidEntity::getEntity();
    AsteroidScript* asteroidScript = dynamic_cast<AsteroidScript*>(ast->getComponentOfType(ComponentType::Script));

    ast->setPosition(getPositionOutOfArena(asteroidScript->getRadius()));

    RigidbodyComponent* rb = dynamic_cast<RigidbodyComponent*>(ast->getComponentOfType(ComponentType::Rigidbody));

    // Add force to move to player
    rb->addForce(VectorUtil::Normalize(playerPos - ast->getPosition()) * asteroidScript->getSpeed());

    Game::getEngine()->getScene()->addEntity(ast);

    asteroids.push_back(ast);
}

