//
// Created by dim on 22/03/2021.
//

#include "CollisionSystem.h"
#include "../components/ScriptComponent.h"
#include "../../Game.h"

CollisionSystem::CollisionSystem() : System(ComponentType::CCollider) {

}

void CollisionSystem::init() {
}

void CollisionSystem::process(std::list<Component*> items) {
    std::vector<ColliderComponent*> colliders = std::vector<ColliderComponent*>();

    for (Component* component : items) {
        ColliderComponent* collider = dynamic_cast<ColliderComponent*>(component);
        colliders.push_back(collider);
    }

    const int colliderCount = (int)colliders.size();

    int colliderOffset = 0;
    for(int x = 0; x < colliderCount; x++){
        colliderOffset++;
        for(int y = colliderOffset; y < colliderCount; y++){
            ColliderComponent* col1 = colliders[x];
            ColliderComponent* col2 = colliders[y];


            if (isCollided(*col1, *col2)) {
                for (Component* component : col1->getEntity()->getComponentsOfType(ComponentType::CScript)) {
                    ScriptComponent* script = dynamic_cast<ScriptComponent*>(component);

                    // Trigger callback
                    script->onCollision(col2->getEntity());
                }

                for (Component* component : col2->getEntity()->getComponentsOfType(ComponentType::CScript)) {
                    ScriptComponent* script = dynamic_cast<ScriptComponent*>(component);

                    // Trigger callback
                    script->onCollision(col1->getEntity());
                }
            }
        }
    }}

bool CollisionSystem::isCollided(const ColliderComponent& col1, const ColliderComponent& col2) {
    // TODO
    return false;
}