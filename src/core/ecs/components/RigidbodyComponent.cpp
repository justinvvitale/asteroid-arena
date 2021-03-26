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

    parent->setPosition(curPosition + (velocity * (1 + Game::dt)));
    parent->setRotation(Rotation(0,0,1, curRotation.angle + this->velRot));
}

void RigidbodyComponent::addForce(float x, float y, float z) {
    addForce(Vector3(x, y, z));
}

void RigidbodyComponent::addForce(Vector3 force) {
    this->velocity = this->velocity + force;
}

void RigidbodyComponent::clearVelocity() {
    this->velocity = Vector3::zero();
    this->velRot = 0;
}

void RigidbodyComponent::setForceRot(float rot) {
    this->velRot = rot;
}
