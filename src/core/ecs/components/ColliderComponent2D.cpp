//
// Created by dim on 22/03/2021.
//

#include "ColliderComponent2D.h"

ColliderComponent2D::ColliderComponent2D(float radius) : Component(ComponentType::CCollider) {
    this->type = ColliderType2D::circlePos;

    this->radius = radius;

}

ColliderComponent2D::ColliderComponent2D(float width, float height) : Component(ComponentType::CCollider) {
    this->type = ColliderType2D::square;

    this->width = width;
    this->height = height;
}

ColliderType2D ColliderComponent2D::getCollisionType() {
    return this->type;
}

std::tuple<float, float> ColliderComponent2D::getSquareDimension() {
    return std::make_tuple(this->width, this->height);
}

float ColliderComponent2D::getCircleRadius() const {
    return radius;
}

void ColliderComponent2D::setOffset(Vector3 offsetIn) {
    this->offset = offsetIn;
}

Vector3 ColliderComponent2D::getOffset() {
    return this->offset;
}

