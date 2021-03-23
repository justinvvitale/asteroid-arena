//
// Created by dim on 21/03/2021.
//

#ifndef I3D_ARENAENTITY_H
#define I3D_ARENAENTITY_H

#include <freeglut.h>
#include "../GAMECONFIG.h"
#include "../../core/ecs/components/MeshComponent.h"

class ArenaEntity {
private:
    static struct Mesh getModel() {
        struct Mesh arenaMesh;
        arenaMesh.mode = GL_LINE_LOOP;
        arenaMesh.data = {
                MeshData(-ARENA_SIZE, -ARENA_SIZE, 0),
                MeshData(ARENA_SIZE, -ARENA_SIZE, 0),
                MeshData(ARENA_SIZE, ARENA_SIZE, 0),
                MeshData(-ARENA_SIZE, ARENA_SIZE, 0)
        };

        return arenaMesh;
    }

public:
    static Entity* getEntity() {
        Entity* arena = new Entity();

        MeshComponent* arenaMeshRender = new MeshComponent();
        arenaMeshRender->setMesh(getModel());
        arena->addComponent(arenaMeshRender);

        arena->setPosition(Vector3(0, 0, 0));

        return arena;
    }

};


#endif //I3D_ARENAENTITY_H
