#include <cstdlib>
#include "entities/PlayerEntity.h"
#include "entities/StationEntity.h"
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
    scene->addEntity(StationEntity::getEntity());

    Entity* waveManagerEntity = new Entity("wave");
    waveManagerEntity->addComponent(new AsteroidWaveScript());

    scene->addEntity(waveManagerEntity);

    return scene;
}

int main(int argc, char** argv) {
    srand((unsigned) time(nullptr));

    // Buffer asteroid textures
    Renderer::loadTexture("asteroid1", "data/texture/asteroid1.jpg");
    Renderer::loadTexture("asteroid2", "data/texture/asteroid2.jpg");
    Renderer::loadTexture("asteroid3", "data/texture/asteroid3.jpg");
    Renderer::loadTexture("asteroid4", "data/texture/asteroid4.jpg");

    // Misc textures
    Renderer::loadTexture("fireball", "data/texture/fireball.png", true);
    Renderer::loadTexture("chunk", "data/texture/chunk.png", true);

    // Run Game
    Game::start(argc, argv, "I3D Assignment 2 - S3718796", getScene);
}
