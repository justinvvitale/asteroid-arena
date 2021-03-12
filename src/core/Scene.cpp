//
// Created by Dimme on 11/03/2021.
//

#include "Scene.h"


void Scene::addEntity(Entity* entity) {
    sceneEntities.push_back(entity);
}

void Scene::removeEntity(Entity* entity) {
    sceneEntities.remove(entity);
}

std::list<Component*> Scene::findComponentsOfType(ComponentType type) {
    std::list<Component*> components = std::list<Component*>();

    for (Entity* entity : sceneEntities) {
        for (Component* component : entity->getComponents()) {
            if (component->getType() == type) {
                components.push_back(component);
            }
        }
    }

    return components;
}

std::unordered_map<ComponentType, std::list<Component*>> Scene::getComponentsByType() {
    std::unordered_map<ComponentType, std::list<Component*>> componentMap = std::unordered_map<ComponentType, std::list<Component*>>();

    for (Entity* entity : sceneEntities) {
        for (Component* component : entity->getComponents()) {
            ComponentType type = component->getType();
            std::unordered_map<ComponentType, std::list<Component*>>::const_iterator iter = componentMap.find(type);

            // If iter has value, key exists and we'll update list, otherwise we make new entry.
            if(iter != componentMap.end()){
                std::list<Component*> componentList = iter->second;
                componentList.push_back(component);
            }else{
                std::list<Component*> componentList = std::list<Component*>();
                componentList.push_back(component);
                componentMap[type] = componentList;
            }
        }
    }

    return componentMap;
}

