//
// Created by dim on 22/03/2021.
//

#include "CollisionSystem2D.h"
#include "../components/ScriptComponent.h"
#include "../../Game.h"

CollisionSystem2D::CollisionSystem2D() : System(ComponentType::CCollider) {

}

void CollisionSystem2D::init() {
}

void CollisionSystem2D::process(std::list<Component*> items) {
    std::list<ColliderComponent2D*> colliders = std::list<ColliderComponent2D*>();

    for (Component* component : items) {
        ColliderComponent2D* collider = dynamic_cast<ColliderComponent2D*>(component);
        colliders.push_back(collider);
    }

    // TODO Could be improved but performance is OK, comparing entity types which should collide is a potential improvement
    const int colliderCount = (int)colliders.size();
    std::vector<ColliderComponent2D*> colliderVec(colliders.begin(), colliders.end());

    int colliderOffset = 0;
    for(int x = 0; x < colliderCount; x++){
        colliderOffset++;
        for(int y = colliderOffset; y < colliderCount; y++){
            ColliderComponent2D* col1 = colliderVec[x];
            ColliderComponent2D* col2 = colliderVec[y];


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
    }
}

bool CollisionSystem2D::isCollided(ColliderComponent2D col1, ColliderComponent2D col2) {
    Vector3 col1Pos = col1.getEntity()->getPosition() + col1.getOffset();
    Vector3 col2Pos = col2.getEntity()->getPosition() + col2.getOffset();

    // Square collision check:
    if (col1.getCollisionType() == ColliderType2D::square && col2.getCollisionType() == ColliderType2D::square) {
        std::tuple<float, float> col1Dims = col1.getSquareDimension();
        std::tuple<float, float> col2Dims = col2.getSquareDimension();

        if (col1Pos.x < col2Pos.x + std::get<0>(col2Dims) &&
            col1Pos.x + std::get<0>(col1Dims) > col2Pos.x &&
            col1Pos.y < col2Pos.y + std::get<1>(col2Dims) &&
            col1Pos.y + std::get<1>(col1Dims) > col2Pos.y) {
            return true;
        }

        return false;
    }

    // Circle collision check:
    if (col1.getCollisionType() == ColliderType2D::circlePos && col2.getCollisionType() == ColliderType2D::circlePos) {
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
    ColliderComponent2D* squareColliderRef;
    ColliderComponent2D* circleColliderRef;

    if (col1.getCollisionType() == ColliderType2D::square) {
        squareColliderRef = &col1;
        circleColliderRef = &col2;
    } else {
        circleColliderRef = &col1;
        squareColliderRef = &col2;
    }

    // We've split which is square and circlePos, now we do the check
    Vector3 squarePos = squareColliderRef->getEntity()->getPosition() + squareColliderRef->getOffset();
    Vector3 circlePos = circleColliderRef->getEntity()->getPosition() + circleColliderRef->getOffset();

    float circleRadius = circleColliderRef->getCircleRadius();
    std::tuple<float, float> squareDims = squareColliderRef->getSquareDimension();
    float squareWidth = std::get<0>(squareDims);
    float squareHeight = std::get<1>(squareDims);


    circlePos.x = abs(circlePos.x - squarePos.x);
    circlePos.y = abs(circlePos.y - squarePos.y);

    if (circlePos.x > (squareWidth / 2 + circleRadius)) {
        return false;
    }
    if (circlePos.y > (squareHeight / 2 + circleRadius)) {
        return false;
    }
    if (circlePos.x <= (squareWidth / 2)) {
        return true;
    }
    if (circlePos.y <= (squareHeight / 2)) {
        return true;
    }

    double cornDistSquared = pow((circlePos.x - squareWidth / 2), 2) + pow((circlePos.y - squareHeight / 2), 2);

    return (cornDistSquared <= (pow(circleRadius, 2)));
}