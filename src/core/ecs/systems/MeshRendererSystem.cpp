//
// Created by Dimme on 11/03/2021.
//

#include <set>
#include "MeshRendererSystem.h"
#include "../../Renderer.h"
#include "../components/ColliderComponent.h"

bool MeshRendererSystem::enabled = true;

MeshRendererSystem::MeshRendererSystem() : System(ComponentType::CMesh) {
}

void MeshRendererSystem::process(std::list<Component*> items) {
    if (!enabled) return;

    std::set<Entity*> rootEntities = std::set<Entity*>();

    // Get root entities
    for (Component* component : items) {
        rootEntities.emplace(getRootEntity(component->getEntity()));
    }

    for (Entity* entity : rootEntities) {
        renderEntity(entity);
    }
}

void MeshRendererSystem::renderEntity(Entity* entity) {
    Renderer::push();

    auto position = entity->getPosition();
    auto rotation = entity->getRotation();

    Renderer::move(position);
    Renderer::rotate(rotation);

    debugRender(entity);

    Component* compMesh = entity->getComponentOfType(ComponentType::CMesh);
    if (compMesh != nullptr) {
        auto* meshComponent = dynamic_cast<MeshComponent*>(compMesh);
        meshComponent->render();
    }

    for (Entity* childEntity : entity->getChildren()) {
        renderEntity(childEntity);
    }

    Renderer::pop();
}

Entity* MeshRendererSystem::getRootEntity(Entity* entity) {
    if (entity->getParent() == nullptr) {
        return entity;
    }

    return getRootEntity(entity->getParent());
}

void MeshRendererSystem::debugRender(Entity* entity) {
    // Particle Emitters
    if (DEBUG_DRAW_PARTICLE_EMITTERS) {
        auto emitterCompList = entity->getComponentsOfType(ComponentType::CParticle);
        Renderer::setColour(DEBUG_DRAW_PARTICLE_EMITTERS_COLOUR);

        for (Component* emitComp : emitterCompList) {
            if (emitComp != nullptr) {
                Vector3 offset = dynamic_cast<ParticleEmitterComponent*>(emitComp)->getOffset();

                Renderer::move(offset);
                Renderer::renderCustom(CustomRender::WireSphere, 0.5);
                Renderer::move(offset.opposite());
            }
        }

        Renderer::setColour(DEFAULT_COLOUR);
    }


    // Colliders
    if (DEBUG_DRAW_COLLIDERS) {
        auto colCompList = entity->getComponentsOfType(ComponentType::CCollider);
        Renderer::setColour(DEBUG_DRAW_COLLIDERS_COLOUR);

        for (Component* colComp : colCompList) {
            if (colComp != nullptr) {
                // TODO
                auto* collider = dynamic_cast<ColliderComponent*>(colComp);
                Vector3 offset = collider->getOffset();

                Renderer::move(offset);

                switch (collider->getCollisionType()) {
                    case cube:
                        Renderer::renderCustom(Cube, collider->getSize());
                        break;
                    case sphere:
                        Renderer::renderCustom(WireSphere, collider->getSize());
                        break;
                }

                // Move to origin
                Renderer::move(offset.opposite());
            }
        }

        Renderer::setColour(DEFAULT_COLOUR);
    }
}

void MeshRendererSystem::setEnabled(bool flag) {
    enabled = flag;
}





