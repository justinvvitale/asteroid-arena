//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_SCENE_H
#define I3D_SCENE_H

#include <typeinfo>
#include <string>
#include <list>
#include <iostream>
#include <unordered_map>
#include "ecs/Entity.h"

class Scene {
private:
    std::list<Entity *> sceneEntities = std::list<Entity *>();


    // Recursive helper functions
    std::list<Component*> findComponentsOfType(Entity* entity, ComponentType type);
    std::list<Entity*> getAllEntities(Entity* entity = nullptr);

public:
    void addEntity(Entity *entity);
    void removeEntity(Entity *entity);

    // Searching
    // Fetches every component of a single type
    std::list<Component*> findComponentsOfType(ComponentType type);

    // Returns a map of componentTypes with every component of that type
    std::unordered_map<ComponentType, std::list<Component*>> getComponentsByType();

};


#endif //I3D_SCENE_H
