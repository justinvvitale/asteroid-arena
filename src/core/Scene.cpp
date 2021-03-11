//
// Created by Dimme on 11/03/2021.
//

#include "Scene.h"


void Scene::addEntity(Entity *entity) {
    sceneEntities.push_back(entity);
}

void Scene::removeEntity(Entity *entity) {
    sceneEntities.remove(entity);
}