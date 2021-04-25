#include <cstdlib>
#include "entities/PlayerEntity.h"
#include "entities/CubeEntity.h"

Scene* getScene() {
    Scene* scene = new Scene();

    scene->addEntity(CubeEntity::getEntity());
    scene->addEntity(PlayerEntity::getEntity());


    return scene;
}

int main(int argc, char** argv) {
    srand((unsigned) time(nullptr));

    // Run Game
    Game::start(argc, argv, "I3D Assignment 2 - S3718796", getScene);
}
