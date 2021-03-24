//
// Created by Dimme on 9/03/2021.
//

#include "Entity.h"
#include "Component.h"

Entity::Entity(EntityTag entityTag) {
    this->tag = entityTag;
}

EntityTag Entity::getTag() {
    return tag;
}


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

std::list<Component*> Entity::getComponentsOfType(ComponentType componentType) {
    std::list<Component*> compList = std::list<Component*>();

    for(Component* component : components){
        if(component->getType() == componentType){
            compList.push_back(component);
        }
    }

    return compList;
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

Entity::~Entity() {
    for(Component* component : components){
        delete component;
    }

    for(Entity* childEntity : children){
        delete childEntity;
    }

}

Vector3 Entity::getWorldPosition() {
    if(parent == nullptr){
        return position;
    }

    Vector3 pos = Vector3::zero();

    std::list<Vector3> vectorModifications = std::list<Vector3>();

    vectorModifications.push_back(this->getPosition());

    Entity* parentEnt = getParent();

    // Traverse the chain and store emitPosition changes
    while(parentEnt != nullptr){
        vectorModifications.push_front(parentEnt->getPosition());
        parentEnt = parentEnt->getParent();
    }

    for(Vector3 vecMod : vectorModifications){
        pos = pos + vecMod;
    }

    return pos;
}








