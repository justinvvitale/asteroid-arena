//
// Created by Dimme on 10/03/2021.
//

#include "Engine.h"
#include "ecs/systems/MeshRendererSystem.h"
#include "ecs/systems/ScriptProcessorSystem.h"
#include "ecs/systems/CollisionSystem.h"
#include "ecs/systems/ParticleSystem.h"
#include "ecs/systems/TextRendererSystem.h"

Engine::Engine() {

    // Shared automatic and manual, kinda special
    ParticleSystem* particleSystem = new ParticleSystem();

    // Setup systems (Priority)
    systems.emplace(ComponentType::CCollider, new CollisionSystem());
    systems.emplace(ComponentType::CScript, new ScriptProcessorSystem());
    systems.emplace(ComponentType::CParticle, particleSystem);

    // Manual systems (Priority)
    manualSystems.emplace(ComponentType::CText, new TextRendererSystem());
    manualSystems.emplace(ComponentType::CMesh, new MeshRendererSystem());
    manualSystems.emplace(ComponentType::CParticle, particleSystem);

    // Init systems
    for (auto const& sys : systems) {
        sys.second->init();
    }
    for (auto const& sys : manualSystems) {
        sys.second->init();
    }
}

void Engine::tick() {
    if (scene == nullptr) return;

    if (bufferDirty) {
        bufferComponentTypes = scene->getComponentsByType();
        bufferDirty = false;
    }

    // Handle components and systems
    for (const auto& compType : bufferComponentTypes) {
        auto iterSystem = systems.find(compType.first);

        if (iterSystem != systems.end()) {
            System* system = (*iterSystem).second;
            system->process(compType.second);
        } else {
            // Doesn't have a system, just tick it.
            for (Component* comp : compType.second) {
                comp->tick();
            }
        }
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

    // Core rendering
    auto componentTypesMesh = bufferComponentTypes.find(ComponentType::CMesh);
    if (componentTypesMesh != bufferComponentTypes.end()) {
        manualSystems[ComponentType::CMesh]->process(componentTypesMesh->second);
    }

    // Particle rendering (Render)
    auto componentTypesParticle = bufferComponentTypes.find(ComponentType::CParticle);
    if (componentTypesParticle != bufferComponentTypes.end()) {
        // Run particle renders then mesh rendering
        manualSystems[ComponentType::CParticle]->render();
    }
}

void Engine::setScene(Scene* sceneIn) {
    delete scene;

    this->scene = sceneIn;
}

Scene* Engine::getScene() {
    return scene;
}

void Engine::resetSystems() {
    manualSystems[ComponentType::CParticle]->cleanup();

}

void Engine::flagDirty() {
    this->bufferDirty = true;
}





