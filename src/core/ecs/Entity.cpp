//
// Created by Dimme on 9/03/2021.
//

#include "Entity.h"

void Entity::tick() {
    for (Component *comp : components) {
        comp->tick();
    }
}

void Entity::addComponent(Component *component) {
    this->components.push_back(component);
}

// Getter/Setter (s)

Vector3 Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const Vector3 &pos) {
    Entity::position = pos;
}

const Quaternion &Entity::getRotation() const {
    return rotation;
}

void Entity::setRotation(const Quaternion &rot) {
    Entity::rotation = rot;
}

std::list<Component *> Entity::getComponents() {
    return components;
}





