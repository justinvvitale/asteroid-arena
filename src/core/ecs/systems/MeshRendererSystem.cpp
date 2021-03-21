//
// Created by Dimme on 11/03/2021.
//

#include <set>
#include "MeshRendererSystem.h"
#include "../Entity.h"

#if _WIN32

#   include <Windows.h>

#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else

#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>

#endif


MeshRendererSystem::MeshRendererSystem() : System(ComponentType::Mesh) {
}

void MeshRendererSystem::process(std::list<Component*> items) {
    std::set<Entity*> rootEntities = std::set<Entity*>();

    // Get root entities
    for(Component* component : items){
        rootEntities.emplace(getRootEntity(component->getParent()));
    }

    for(Entity* entity : rootEntities){
        renderEntity(entity);
    }
}

void MeshRendererSystem::renderEntity(Entity* entity) {
    glPushMatrix();

    auto position = entity->getPosition();
    auto rotation = entity->getRotation();

    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.w, rotation.x, rotation.y, rotation.z);


    Component* compMesh = entity->getComponentOfType(ComponentType::Mesh);
    if(compMesh != nullptr){
        auto* meshComponent = dynamic_cast<MeshComponent*>(compMesh);
        meshComponent->render();
    }

    for(Entity* childEntity : entity->getChildren()){
        renderEntity(entity);
    }

    glPopMatrix();
}

Entity* MeshRendererSystem::getRootEntity(Entity* entity) {
    if(entity->getParent() == nullptr){
        return entity;
    }

    return getRootEntity(entity);
}



