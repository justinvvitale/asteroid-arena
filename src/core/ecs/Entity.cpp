//
// Created by Dimme on 9/03/2021.
//

#include "Entity.h"
#include "Component.h"

void Entity::tick() {
    for (Component *comp : components) {
        comp->tick();
    }
}

void Entity::addComponent(Component* component) {
    component->setParent(this);
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

Component* Entity::getComponentOfType(ComponentType componentType) {
    for(Component* component : components){
        if(component->getType() == componentType){
            return component;
        }
    }

    return nullptr;
}

Entity* Entity::getParent() {
    return parent;
}

void Entity::setParent(Entity* entity) {
    this->parent = entity;
    entity->children.push_back(entity);
}

std::list<Entity*> Entity::getChildren() {
    return children;
}







