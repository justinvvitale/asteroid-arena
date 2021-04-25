//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_ENGINE_H
#define I3D_ENGINE_H

#include "ecs/System.h"
#include "Scene.h"
#include "ecs/components/CameraComponent.h"
#include <unordered_map>

class Engine {
private:
    // Variables
    Scene* scene = nullptr;

    std::unordered_map<ComponentType, System*> systems = std::unordered_map<ComponentType, System*>();
    std::unordered_map<ComponentType, System*> manualSystems = std::unordered_map<ComponentType, System*>();

    bool bufferDirty = true;
    std::unordered_map<ComponentType, std::list<Component*>> bufferComponentTypes = std::unordered_map<ComponentType, std::list<Component*>>();
public:
    CameraComponent* camera = nullptr;

    Engine();

    void tick();

    void render();

    void setScene(Scene* sceneIn);

    Scene* getScene();

    void resetSystems();

    void flagDirty();
};


#endif //I3D_ENGINE_H
