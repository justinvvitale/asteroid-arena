//
// Created by Dimme on 10/03/2021.
//

#include "Engine.h"
#include "ecs/systems/MeshRendererSystem.h"
#include "ecs/systems/ScriptProcessorSystem.h"
#include "ecs/systems/CollisionSystem.h"
#include "ecs/systems/ParticleSystem.h"

Engine::Engine() {

    // Setup systems (Priority)
    systems.push_back(new CollisionSystem());
    systems.push_back(new ScriptProcessorSystem());

    // Manual systems (Priority)
    manualSystems.emplace(ComponentType::CMesh, new MeshRendererSystem());
    manualSystems.emplace(ComponentType::CParticle, new ParticleSystem());

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

    bufferComponentTypes = scene->getComponentsByType();

    // System handling
    for(System* system : systems){

        auto componentTypeIter = bufferComponentTypes.find(system->getType());
        // If we can't find it, then it probably doesn't exist, don't need to process system.
        if(componentTypeIter == bufferComponentTypes.end()) continue;

        system->process(componentTypeIter->second);

        // Remove processed type
        bufferComponentTypes.erase(system->getType());
    }

    // Tick any components which don't have a system directly managing them (Or manual)
    for (auto& compType: bufferComponentTypes) {
        if(manualSystems[compType.first] == nullptr){
            for(Component* comp : compType.second){
                comp->tick();
            }
        }
    }

    // Particle rendering (Tick)
    auto componentTypesParticle = bufferComponentTypes.find(ComponentType::CParticle);
    if(componentTypesParticle != bufferComponentTypes.end()){
        // Run particle renders then mesh rendering
        manualSystems[ComponentType::CParticle]->process(componentTypesParticle->second);
    }
}

void Engine::render() {

    // Particle rendering (Render)
    auto componentTypesParticle = bufferComponentTypes.find(ComponentType::CParticle);
    if(componentTypesParticle != bufferComponentTypes.end()){
        // Run particle renders then mesh rendering
        manualSystems[ComponentType::CParticle]->render();
    }

    // Core rendering
    auto componentTypesMesh = bufferComponentTypes.find(ComponentType::CMesh);
    if(componentTypesMesh != bufferComponentTypes.end()){
        manualSystems[ComponentType::CMesh]->process(componentTypesMesh->second);
    }
}

void Engine::setScene(Scene* sceneIn) {
    delete scene;

    this->scene = sceneIn;
}

Scene* Engine::getScene() {
    return scene;
}

void Engine::ResetSystems() {
    manualSystems[ComponentType::CParticle]->cleanup();

}





