//
// Created by dim on 21/03/2021.
//

#ifndef I3D_ARENAENTITY_H
#define I3D_ARENAENTITY_H

#include "../GAMECONFIG.h"
#include "../../core/ecs/components/MeshComponent.h"
#include "../scripts/WallScript.h"

class ArenaEntity {
private:

public:
    static void addColliders(Entity* entity) {
//        // We'll add one for each side
//
//        float bufferSize = 1000;
//        float halfWidth = ARENA_WIDTH / 2;
//        float halfHeight = ARENA_HEIGHT / 2;
//
//        // This could be improved with a loo
//        // Left
//        ColliderComponent2D* leftCol = new ColliderComponent2D(bufferSize, ARENA_HEIGHT*2);
//        leftCol->setOffset(Vector3(-halfWidth - bufferSize / 2, 0, 0));
//        // Right
//        ColliderComponent2D* rightCol = new ColliderComponent2D(bufferSize, ARENA_HEIGHT*2);
//        rightCol->setOffset(Vector3(halfWidth + bufferSize / 2, 0, 0));
//        // Top
//        ColliderComponent2D* topCol = new ColliderComponent2D(ARENA_HEIGHT, bufferSize*2);
//        topCol->setOffset(Vector3(0, halfHeight + bufferSize, 0));
//        // Bottom
//        ColliderComponent2D* bottomCol = new ColliderComponent2D(ARENA_HEIGHT, bufferSize*2);
//        bottomCol->setOffset(Vector3(0, -halfHeight - bufferSize, 0));
//
//        entity->addComponent(leftCol);
//        entity->addComponent(rightCol);
//        entity->addComponent(topCol);
//        entity->addComponent(bottomCol);

    }

    static Mesh getModel() {
        Mesh mesh;
        float arenaSize = 1000;
        mesh.mode = GL_POLYGON;
        mesh.data = {
                MeshData(arenaSize, 0, arenaSize),
                MeshData(arenaSize, 0, -arenaSize),
                MeshData(-arenaSize, 0, -arenaSize),
                MeshData(-arenaSize, 0, arenaSize)
        };

        return mesh;
    }

    static Entity* getEntity() {
        Entity* arena = new Entity("arena");

        MeshComponent* arenaMeshRender = new MeshComponent();
        arenaMeshRender->setMesh(getModel());
        arena->addComponent(arenaMeshRender);

        arena->addComponent(new WallScript());

        addColliders(arena);

        arena->setPosition(Vector3(0, 0, 0));

        return arena;
    }
};


#endif //I3D_ARENAENTITY_H
