//
// Created by Dimme on 9/03/2021.
//

#include "Entity.h"

#include <utility>
#include "Component.h"
#include "../Game.h"

Entity::Entity(std::string tag) {
    this->tag = std::move(tag);
}

std::string Entity::getTag() {
    return tag;
}


void Entity::tick() {
    for (Component* comp : components) {
        comp->tick();
    }
}

void Entity::addComponent(Component* component) {
    component->setParent(this);
    this->components.push_back(component);

    Game::getEngine()->flagDirty();
}

// Getter/Setter (s)

Vector3 Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const Vector3& pos) {
    Entity::position = pos;
}

void Entity::setPosition(float x, float y, float z) {
    Entity::position = Vector3(x,y,z);
}


Rotation Entity::getRotation() const {
    return rotation;
}

void Entity::setRotation(const Rotation& rot) {
    Entity::rotation = rot;
}

std::list<Component*> Entity::getComponents() {
    return components;
}

std::list<Component*> Entity::getComponentsOfType(ComponentType componentType) {
    std::list<Component*> compList = std::list<Component*>();

    for (Component* component : components) {
        if (component->getType() == componentType) {
            compList.push_back(component);
        }
    }

    return compList;
}

Component* Entity::getComponentOfType(ComponentType componentType) {
    for (Component* component : components) {
        if (component->getType() == componentType) {
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
}

std::list<Entity*> Entity::getChildren() {
    return children;
}

Entity::~Entity() {
    for (Component* component : components) {
        delete component;
    }

    for (Entity* childEntity : children) {
        delete childEntity;
    }

}

Vector3 Entity::getWorldPosition() {
    if (parent == nullptr) {
        return position;
    }

    Vector3 pos = Vector3::zero();

    std::list<Vector3> vectorModifications = std::list<Vector3>();

    vectorModifications.push_back(this->getPosition());

    Entity* parentEnt = getParent();

    // Traverse the chain and store emitPosition changes
    while (parentEnt != nullptr) {
        vectorModifications.push_front(parentEnt->getPosition());
        parentEnt = parentEnt->getParent();
    }

    for (Vector3 vecMod : vectorModifications) {
        pos = pos + vecMod;
    }

    return pos;
}

Component* Entity::getComponentOfTypeInChildren(ComponentType componentType) {
    Component* comp = nullptr;
    for (Entity* childEntity: children) {
        comp = childEntity->getComponentOfType(componentType);

        if (comp != nullptr) {
            return comp;
        }
    }

    return comp;
}

void Entity::addChild(Entity* entity) {
    this->children.push_back(entity);
    entity->setParent(this);

    Game::getEngine()->flagDirty();
}

void Entity::removeChild(Entity* entity) {
    // Should only be called by scene remove func (Sets dirty)
    this->children.remove(entity);
}

void Entity::destroy() {
    Engine* engine = Game::getEngine();
    engine->getScene()->removeEntity(this);
    engine->flagDirty();

    Game::queueEntityCleanup(this);
}

void Entity::removeComponent(Component* component) {
    auto compIter = components.begin();

    while (compIter != components.end()) {
        Component* curComp = *compIter;
        if (curComp == component) {
            components.erase(compIter);
            return;
        }

        ++compIter;
    }
}

std::list<Entity*> Entity::getHierarchicalEntities() {
    std::list<Entity*> entities = std::list<Entity*>();
    for(Entity* child : getChildren()){
        std::list<Entity*> childOfChild = child->getHierarchicalEntities();
        entities.insert(entities.begin(), childOfChild.begin(), childOfChild.end());
    }

    entities.push_back(this);

    return entities;
}










