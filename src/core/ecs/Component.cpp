//
// Created by Dimme on 10/03/2021.
//

#include "Component.h"

Component::Component(ComponentType type) : type(type) {
}

ComponentType Component::getType() {
    return type;
}

void Component::setParent(Entity *entity) {
    this->parent = entity;
}

Entity* Component::getEntity() {
    return parent;
}


