//
// Created by dim on 21/04/2021.
//

#include "ColliderComponent.h"

ColliderComponent::ColliderComponent() : Component(ComponentType::CCollider) {
    this->type = ColliderType::cube;
}

ColliderType ColliderComponent::getCollisionType() {
    return this->type;
}

void ColliderComponent::setOffset(Vector3 offsetIn) {
    this->offset = offsetIn;
}

Vector3 ColliderComponent::getOffset() {
    return this->offset;
}