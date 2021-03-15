//
// Created by Dimme on 10/03/2021.
//

#include "Engine.h"
#include "ecs/systems/MeshRendererSystem.h"

Engine::Engine() {

    // Setup systems (Priority)
    systems.push_back(new MeshRendererSystem());


    // Init systems
    for(System* system : systems){
        system->init();
    }
}

void Engine::tick() {
    if(scene == nullptr) return;


    // System handling
    auto componentsByType = scene->getComponentsByType();
    for(System* system : systems){

        auto componentTypeIter = componentsByType.find(system->getType());
        // If we can't find it, then it probably doesn't exist, don't need to process system.
        if(componentTypeIter == componentsByType.end()) continue;

        system->process(componentTypeIter->second);
    }
}

void Engine::render() {
    tick();
}

void Engine::setScene(Scene* sceneIn) {
    this->scene = sceneIn;
}

Scene* Engine::getScene() {
    return scene;
}






