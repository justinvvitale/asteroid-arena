//
// Created by Dimme on 11/03/2021.
//

#include <set>
#include "MeshRendererSystem.h"
#include "../../ENGINECONFIG.h"
#include "../components/ColliderComponent.h"
#include "../../Renderer.h"


MeshRendererSystem::MeshRendererSystem() : System(ComponentType::Mesh) {
}

void MeshRendererSystem::process(std::list<Component*> items) {
    std::set<Entity*> rootEntities = std::set<Entity*>();

    // Get root entities
    for(Component* component : items){
        rootEntities.emplace(getRootEntity(component->getParent()));
    }

    for(Entity* entity : rootEntities){
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

    Component* compMesh = entity->getComponentOfType(ComponentType::Mesh);
    if(compMesh != nullptr){
        auto* meshComponent = dynamic_cast<MeshComponent*>(compMesh);
        meshComponent->render();
    }

    for(Entity* childEntity : entity->getChildren()){
        renderEntity(childEntity);
    }

    Renderer::pop();
}

Entity* MeshRendererSystem::getRootEntity(Entity* entity) {
    if(entity->getParent() == nullptr){
        return entity;
    }

    return getRootEntity(entity);
}

void MeshRendererSystem::debugRender(Entity* entity) {
    // Colliders
    if(DEBUG_DRAW_COLLIDERS){
        Component* colComp = entity->getComponentOfType(ComponentType::Collider);
        Renderer::setColour(DEBUG_DRAW_COLLIDERS_COLOUR);

        if(colComp != nullptr){
            auto* collider = dynamic_cast<ColliderComponent*>(colComp);
            Vector3 offset = collider->getOffset();

            Renderer::move(offset);

            switch (collider->getCollisionType()) {
                case circlePos:
                        Renderer::drawCircle(collider->getCircleRadius());
                    break;
                case square:
                    std::tuple<float,float> dims = collider->getSquareDimension();
                    Renderer::drawRect(std::get<0>(dims), std::get<1>(dims));
                    break;
            }

            // Move to origin
            Renderer::move(offset.opposite());
        }

        Renderer::setColour(DEFAULT_COLOUR);
    }
}





