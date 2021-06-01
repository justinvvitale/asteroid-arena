#include <cstdlib>
#include "entities/PlayerEntity.h"
#include "entities/CubeEntity.h"
#include "entities/MediatorEntity.h"
#include "entities/ScoreManagerEntity.h"
#include "entities/ArenaEntity.h"
#include "entities/AsteroidEntity.h"
#include "entities/CameraEntity.h"

Scene* getScene() {
    Scene* scene = new Scene();

    scene->addEntity(MediatorEntity::getEntity());
    scene->addEntity(ScoreManagerEntity::getEntity());

    scene->addEntity(CameraEntity::getEntity());

    scene->addEntity(PlayerEntity::getEntity());

    scene->addEntity(ArenaEntity::getEntity());
    scene->addEntity(CubeEntity::getEntity());

    Entity* waveManagerEntity = new Entity("wave");
    waveManagerEntity->addComponent(new AsteroidWaveScript());

    scene->addEntity(waveManagerEntity);

    return scene;
}

int main(int argc, char** argv) {
    srand((unsigned) time(nullptr));

    // Run Game
    Game::start(argc, argv, "I3D Assignment 2 - S3718796", getScene);
}
