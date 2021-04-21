//
// Created by dim on 21/04/2021.
//

#include "ColliderComponent3D.h"

ColliderComponent3D::ColliderComponent3D() : Component(ComponentType::CCollider) {
    this->type = ColliderType3D::cube;
}

ColliderType3D ColliderComponent3D::getCollisionType() {
    return this->type;
}

void ColliderComponent3D::setOffset(Vector3 offsetIn) {
    this->offset = offsetIn;
}

Vector3 ColliderComponent3D::getOffset() {
    return this->offset;
}