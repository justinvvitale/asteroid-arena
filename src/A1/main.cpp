#include "../core/Game.h"
#include "entities/ArenaEntity.h"
#include "entities/ShipEntity.h"
#include "scripts/AsteroidWaveScript.h"
#include "entities/ScoreManagerEntity.h"
#include "entities/MediatorEntity.h"

#include <ctime>

// 0 Initial 1 Playing 2 End
static int playState = 0;

Scene* getScene() {
    Scene* scene = new Scene();
    scene->addEntity(MediatorEntity::getEntity());

    scene->addEntity(ArenaEntity::getEntity());
    scene->addEntity(ShipEntity::getEntity());
    scene->addEntity(ScoreManagerEntity::getEntity());

    Entity* waveManagerEntity = new Entity();
    waveManagerEntity->addComponent(new AsteroidWaveScript());

    scene->addEntity(waveManagerEntity);

    return scene;
}

int main(int argc, char** argv) {
    srand((unsigned) time(nullptr));

    // Run Game
    Game::start(argc, argv, "I3D Assignment 1 - S3718796", getScene);
}

