#include "../core/Game.h"
#include "../core/ecs/components/MeshComponent.h"
#include "entities/arenaEntity.h"
#include "entities/shipEntity.h"

int main(int argc, char **argv) {

    // Setup Engine
    Engine* engine = new Engine();

    Scene* scene = new Scene();
        scene->addEntity(ArenaEntity::getEntity());
        scene->addEntity(ShipEntity::getEntity());
    engine->setScene(scene);


    // Run Game
    Game::start(argc, argv, "I3D Assignment 1 - S3718796", engine);
}