//
// Created by dim on 24/03/2021.
//

#include "RigidbodyComponent.h"
#include "../../Game.h"

RigidbodyComponent::RigidbodyComponent() : Component(ComponentType::CRigidbody) {

}

void RigidbodyComponent::tick() {
    // Apply velocity
    Entity* parent = this->getEntity();
    Vector3 curPosition = parent->getPosition();
    Rotation curRotation = parent->getRotation();

    parent->setPosition(curPosition + (velocity * Game::dt));
    //parent->setRotation(Rotation(0, 0, 1, curRotation.angle + (this->spin * Game::dt))); TODO
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

void RigidbodyComponent::setSpin(float amount) {
    this->spin = amount;
}

Vector3 RigidbodyComponent::getVelocity() {
    return {this->velocity};
}

float RigidbodyComponent::getSpin() const {
    return spin;
}
