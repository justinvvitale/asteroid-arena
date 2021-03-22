//
// Created by dim on 22/03/2021.
//

#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(float radius) : Component(ComponentType::Collider) {
    this->type = ColliderType::circlePos;

    this->radius = radius;

}

ColliderComponent::ColliderComponent(float width, float height) : Component(ComponentType::Collider) {
    this->type = ColliderType::square;

    this->width = width;
    this->height = height;
}

ColliderType ColliderComponent::getCollisionType() {
    return this->type;
}

std::tuple<float, float> ColliderComponent::getSquareDimension() {
    return std::make_tuple(this->width, this->height);
}

float ColliderComponent::getCircleRadius() const {
    return radius;
}

