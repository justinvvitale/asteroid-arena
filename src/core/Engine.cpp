//
// Created by Dimme on 10/03/2021.
//

#include "Engine.h"
#include "ecs/systems/MeshRendererSystem.h"
#include "ecs/systems/ScriptProcessorSystem.h"
#include "ecs/systems/CollisionSystem.h"

Engine::Engine() {

    // Setup systems (Priority)
    systems.push_back(new CollisionSystem());
    systems.push_back(new ScriptProcessorSystem());

    // Manual systems (Priority)
    manualSystems.emplace(ComponentType::Mesh, new MeshRendererSystem());


    // Init systems
    for(System* system : systems){
        system->init();
    }
    for (auto const& sys : manualSystems){
        sys.second->init();
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
    auto componentsByType = scene->getComponentsByType();
    auto componentTypeIter = componentsByType.find(ComponentType::Mesh);
    if(componentTypeIter == componentsByType.end()) return;
    manualSystems[ComponentType::Mesh]->process(componentTypeIter->second);
}

void Engine::setScene(Scene* sceneIn) {
    delete scene;

    this->scene = sceneIn;
}

Scene* Engine::getScene() {
    return scene;
}






