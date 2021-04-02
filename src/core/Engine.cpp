//
// Created by Dimme on 10/03/2021.
//

#include "Engine.h"
#include "ecs/systems/MeshRendererSystem.h"
#include "ecs/systems/ScriptProcessorSystem.h"
#include "ecs/systems/CollisionSystem.h"
#include "ecs/systems/ParticleSystem.h"
#include "ecs/systems/TextRendererSystem.h"

#include <unordered_set>

Engine::Engine() {

    // Setup systems (Priority)
    systems.push_back(new CollisionSystem());
    systems.push_back(new ScriptProcessorSystem());

    // Manual systems (Priority)
    manualSystems.emplace(ComponentType::CText, new TextRendererSystem());
    manualSystems.emplace(ComponentType::CMesh, new MeshRendererSystem());
    manualSystems.emplace(ComponentType::CParticle, new ParticleSystem());

    // Init systems
    for (System* system : systems) {
        system->init();
        processedSystemTypes.emplace(system->getType());
    }
    for (auto const& sys : manualSystems) {
        sys.second->init();
        processedSystemTypes.emplace(sys.first);
    }
}

void Engine::tick() {
    if (scene == nullptr) return;

    if (bufferDirty) {
        bufferComponentTypes = scene->getComponentsByType();
        bufferDirty = false;
    }

    // System handling
    for (System* system : systems) {
        auto componentTypeIter = bufferComponentTypes.find(system->getType());
        // If we can't find it, then it probably doesn't exist, don't need to process system.
        if (componentTypeIter == bufferComponentTypes.end()) continue;

        system->process(componentTypeIter->second);
    }

    // Tick any components which don't have a system directly managing them (Or manual)
    for (auto& compType: bufferComponentTypes) {
//        if (processedSystemTypes.count(compType.first) == 0) { // TODO make it only call once cheaply
            for (Component* comp : compType.second) {
                comp->tick();
            }
//        }
    }

    // Particle rendering (Tick)
    auto componentTypesParticle = bufferComponentTypes.find(ComponentType::CParticle);
    if (componentTypesParticle != bufferComponentTypes.end()) {
        // Run particle renders then mesh rendering
        manualSystems[ComponentType::CParticle]->process(componentTypesParticle->second);
    }
}

void Engine::render() {
    if (bufferDirty) {
        bufferComponentTypes = scene->getComponentsByType();
        bufferDirty = false;
    }

    // Text rendering
    auto componentTypesText = bufferComponentTypes.find(ComponentType::CText);
    if (componentTypesText != bufferComponentTypes.end()) {
        manualSystems[ComponentType::CText]->process(componentTypesText->second);
    }

    // Particle rendering (Render)
    auto componentTypesParticle = bufferComponentTypes.find(ComponentType::CParticle);
    if (componentTypesParticle != bufferComponentTypes.end()) {
        // Run particle renders then mesh rendering
        manualSystems[ComponentType::CParticle]->render();
    }

    // Core rendering
    auto componentTypesMesh = bufferComponentTypes.find(ComponentType::CMesh);
    if (componentTypesMesh != bufferComponentTypes.end()) {
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

void Engine::flagDirty() {
    this->bufferDirty = true;
}





