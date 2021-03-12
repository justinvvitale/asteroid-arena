//
// Created by Dimme on 10/03/2021.
//

#include "Component.h"

Component::Component(ComponentType type) : type(type) {
}

void Component::setParent(Entity *entity) {
    this->parent = entity;
}

ComponentType Component::getType() {
    return type;
}


