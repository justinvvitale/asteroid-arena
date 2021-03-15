//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_ENGINE_H
#define I3D_ENGINE_H

#include "ecs/System.h"
#include "Scene.h"

class Engine {
private:
    Engine();

    // Variables
    Scene* scene = nullptr;

    std::list<System*> systems = std::list<System*>();

public:
    static Engine &getInstance() {
        static Engine instance;
        return instance;
    }

    Engine(Engine const &) = delete;

    void operator=(Engine const &) = delete;

    void tick();
    void render();

    void setScene(Scene* sceneIn);
    Scene* getScene();
};


#endif //I3D_ENGINE_H
