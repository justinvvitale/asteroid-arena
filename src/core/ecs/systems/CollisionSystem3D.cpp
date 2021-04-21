//
// Created by dim on 22/03/2021.
//

#include "CollisionSystem3D.h"
#include "../components/ScriptComponent.h"
#include "../../Game.h"

CollisionSystem3D::CollisionSystem3D() : System(ComponentType::CCollider) {

}

void CollisionSystem3D::init() {
}

void CollisionSystem3D::process(std::list<Component*> items) {
    std::list<ColliderComponent3D*> colliders = std::list<ColliderComponent3D*>();

    for (Component* component : items) {
        ColliderComponent3D* collider = dynamic_cast<ColliderComponent3D*>(component);
        colliders.push_back(collider);
    }

    // TODO Could be improved but performance is OK, comparing entity types which should collide is a potential improvement
    for (ColliderComponent3D* collider : colliders) {
        for (ColliderComponent3D* otherCollider : colliders) {
            // Ignore if is same collider
            if (collider == otherCollider) {
                continue;
            }

            if (isCollided(*collider, *otherCollider)) {
                for (Component* component : collider->getEntity()->getComponentsOfType(ComponentType::CScript)) {
                    ScriptComponent* script = dynamic_cast<ScriptComponent*>(component);

                    // Trigger callback
                    script->onCollision(otherCollider->getEntity());
                }
            }
        }
    }
}

bool CollisionSystem3D::isCollided(const ColliderComponent3D& col1, const ColliderComponent3D& col2) {
    // TODO
    return false;
}