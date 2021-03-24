//
// Created by dim on 24/03/2021.
//

#include "RigidbodyComponent.h"
#include "../../Game.h"

RigidbodyComponent::RigidbodyComponent() : Component(ComponentType::CRigidbody) {

}

void RigidbodyComponent::tick() {
    // Apply velocity
    Entity* parent = this->getParent();
    Vector3 curPosition = parent->getPosition();

    parent->setPosition(curPosition + (velocity *  (1 + Game::dt)));
}

void RigidbodyComponent::addForce(float x, float y, float z) {
    addForce(Vector3(x, y, z));
}

void RigidbodyComponent::addForce(Vector3 force) {
    this->velocity = this->velocity + force;
}

void RigidbodyComponent::clearVelocity() {
    this->velocity = Vector3::zero();
}
