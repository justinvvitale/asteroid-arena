//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_ENGINE_H
#define I3D_ENGINE_H

#include "ecs/System.h"
#include "Scene.h"
#include <map>

class Engine {
private:
    // Variables
    Scene* scene = nullptr;

    std::list<System*> systems = std::list<System*>();
    std::map<ComponentType, System*> manualSystems = std::map<ComponentType, System*>();

    std::unordered_map<ComponentType, std::list<Component*>> bufferComponentTypes = std::unordered_map<ComponentType, std::list<Component*>>();
public:
    Engine();

    void tick();
    void render();

    void setScene(Scene* sceneIn);
    Scene* getScene();

    void ResetSystems();
};


#endif //I3D_ENGINE_H
