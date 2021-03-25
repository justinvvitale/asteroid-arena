//
// Created by dim on 22/03/2021.
//

#include "CollisionSystem.h"
#include "../components/ScriptComponent.h"

CollisionSystem::CollisionSystem() : System(ComponentType::CCollider) {

}

void CollisionSystem::init() {
}

void CollisionSystem::process(std::list<Component*> items) {

    std::list<ColliderComponent*> colliders = std::list<ColliderComponent*>();

    for(Component* component : items){
        ColliderComponent* collider = dynamic_cast<ColliderComponent*>(component);
        colliders.push_back(collider);
    }

    // TODO prevent duplicate checks for checking same colliders twice
    for(ColliderComponent* collider : colliders){
        for(ColliderComponent* otherCollider : colliders){
            // Ignore if is same collider
            if(collider == otherCollider){
                continue;
            }

            if(isCollided(*collider, *otherCollider)){
                for(Component* component : collider->getEntity()->getComponentsOfType(ComponentType::CScript)){
                    ScriptComponent* script = dynamic_cast<ScriptComponent*>(component);

                    // Trigger callback
                    script->onCollision(otherCollider->getEntity());
                }
            }
        }
    }
}

bool CollisionSystem::isCollided(ColliderComponent col1, ColliderComponent col2) {
    Vector3 col1Pos = col1.getEntity()->getPosition() + col1.getOffset();
    Vector3 col2Pos = col2.getEntity()->getPosition() + col2.getOffset();

    // Square collision check:
    if(col1.getCollisionType() == ColliderType::square && col2.getCollisionType() == ColliderType::square){
        std::tuple<float,float> col1Dims = col1.getSquareDimension();
        std::tuple<float,float> col2Dims = col2.getSquareDimension();

        if (col1Pos.x < col2Pos.x + std::get<0>(col2Dims) &&
            col1Pos.x + std::get<0>(col1Dims) > col2Pos.x &&
            col1Pos.y < col2Pos.y + std::get<1>(col2Dims) &&
            col1Pos.y + std::get<1>(col1Dims) > col2Pos.y) {
            return true;
        }

        return false;
    }

    // Circle collision check:
    if(col1.getCollisionType() == ColliderType::circlePos && col2.getCollisionType() == ColliderType::circlePos){
        float dx = col1Pos.x - col2Pos.x;
        float dy = col1Pos.y - col2Pos.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < col1.getCircleRadius() + col2.getCircleRadius()) {
            return true;
        }

        return false;
    }

    // This does not support any new types, should be re-designed in future if more colliders are added.

    // Circle Square collision check:
    ColliderComponent* squareColliderRef;
    ColliderComponent* circleColliderRef;

    if(col1.getCollisionType() == ColliderType::square){
        squareColliderRef = &col1;
        circleColliderRef = &col2;
    }else{
        circleColliderRef = &col1;
        squareColliderRef = &col2;
    }

    // We've split which is square and circlePos, now we do the check
    Vector3 squarePos = squareColliderRef->getEntity()->getPosition() + squareColliderRef->getOffset();
    Vector3 circlePos = circleColliderRef->getEntity()->getPosition() + circleColliderRef->getOffset();

    float circleRadius = circleColliderRef->getCircleRadius();
    std::tuple<float,float> squareDims = squareColliderRef->getSquareDimension();
    float squareWidth = std::get<0>(squareDims);
    float squareHeight = std::get<1>(squareDims);


    circlePos.x = abs(circlePos.x - squarePos.x);
    circlePos.y = abs(circlePos.y - squarePos.y);

    if (circlePos.x > (squareWidth/2 + circleRadius)) {
        return false;
    }
    if (circlePos.y > (squareHeight/2 + circleRadius)) {
        return false;
    }
    if (circlePos.x <= (squareWidth/2)) {
        return true;
    }
    if (circlePos.y <= (squareHeight/2)) {
        return true;
    }

    double cornDistSquared = pow((circlePos.x - squareWidth/2), 2) + pow((circlePos.y - squareHeight/2), 2);

    return (cornDistSquared <= (pow(circleRadius, 2)));
}