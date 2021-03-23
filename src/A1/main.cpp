#include "../core/Game.h"
#include "entities/ArenaEntity.h"
#include "entities/TestEntity.h"
#include "entities/ShipEntity.h"

Scene* getScene(){
    Scene* scene = new Scene();
        scene->addEntity(ArenaEntity::getEntity());
        scene->addEntity(ShipEntity::getEntity());
        scene->addEntity(TestEntity::getEntity());

    return scene;
}

int main(int argc, char** argv) {
    bool shouldExit = false;

    // Run Game
    Game::start(argc, argv, "I3D Assignment 1 - S3718796", getScene);
}

