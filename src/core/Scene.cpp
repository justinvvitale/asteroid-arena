//
// Created by Dimme on 11/03/2021.
//

#include "Scene.h"
#include "ecs/Component.h"
#include "Game.h"

void Scene::addEntity(Entity* entity) {
    sceneEntities.push_back(entity);

    // Check for tags (Down the tree)
    for(Entity* hEntity : entity->getHierarchicalEntities()){
        std::string tag = hEntity->getTag();
        if (!tag.empty()) {
            this->taggedEntities[tag] = hEntity;
        }
    }
}

void Scene::removeEntity(Entity* entity) {
    // If root entity, just remove, otherwise we gotta cleanup child entity
    if (entity->getParent() == nullptr) {
        sceneEntities.remove(entity);
    } else {
        entity->getParent()->removeChild(entity);
    }

    std::string tag = entity->getTag();
    if (!tag.empty() && this->taggedEntities[tag] == entity) {
        this->taggedEntities[tag] = nullptr;
    }

    Game::getEngine()->flagDirty();
}

std::list<Component*> Scene::findComponentsOfType(ComponentType type) {
    std::list<Component*> components = std::list<Component*>();

    for (Entity* entity : sceneEntities) {
        components.splice(components.end(), this->findComponentsOfType(entity, type));
    }

    return components;
}

std::unordered_map<ComponentType, std::list<Component*>> Scene::getComponentsByType() {
    std::unordered_map<ComponentType, std::list<Component*>> componentMap = std::unordered_map<ComponentType, std::list<Component*>>();

    for (Entity* entity : getAllEntities()) {
        for (Component* component : entity->getComponents()) {
            ComponentType type = component->getType();

            auto iter = componentMap.find(type);

            // If iter has value, key exists and we'll update list, otherwise we make new entry.
            if (iter != componentMap.end()) {
                std::list<Component*>& componentList = iter->second;
                componentList.push_back(component);
            } else {
                std::list<Component*> componentList = std::list<Component*>();
                componentList.push_back(component);
                componentMap[type] = componentList;
            }
        }
    }

    return componentMap;
}


// Helper recursive for traversing the vast scene
std::list<Component*> Scene::findComponentsOfType(Entity* entity, ComponentType type) {
    std::list<Component*> components = std::list<Component*>();

    for (Component* component : entity->getComponents()) {
        if (component->getType() == type) {
            components.push_back(component);
        }
    }

    for (Entity* child : entity->getChildren()) {
        components.splice(components.end(), this->findComponentsOfType(child, type));
    }

    return components;
}

std::list<Entity*> Scene::getAllEntities(Entity* entity) {
    std::list<Entity*> entities = std::list<Entity*>();

    if (entity == nullptr) {
        for (Entity* sceneEntity : this->sceneEntities) {
            entities.splice(entities.end(), this->getAllEntities(sceneEntity));
        }

        return entities;
    }

    entities.push_back(entity);

    for (Entity* child : entity->getChildren()) {
        entities.splice(entities.end(), this->getAllEntities(child));
    }

    return entities;
}

Entity* Scene::getEntity(const std::string& tag) {
    return this->taggedEntities[tag];
}

Scene::~Scene() {
    for (Entity* entity : sceneEntities) {
        delete entity;
    }
}

