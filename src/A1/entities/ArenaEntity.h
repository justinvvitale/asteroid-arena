//
// Created by dim on 21/03/2021.
//

#ifndef I3D_ARENAENTITY_H
#define I3D_ARENAENTITY_H

#include <freeglut.h>
#include "../GAMECONFIG.h"
#include "../../core/ecs/components/MeshComponent.h"
#include "../scripts/WallScript.h"
#include "../../core/ecs/components/ColliderComponent.h"

class ArenaEntity {
private:

public:
    static void addColliders(Entity* entity) {
        // We'll add one for each side

        float bufferSize = 500;
        float halfWidth = ARENA_WIDTH / 2;
        float halfHeight = ARENA_HEIGHT / 2;

        // This could be improved with a loop

        // Left
        ColliderComponent* leftCol = new ColliderComponent(bufferSize, ARENA_HEIGHT);
        leftCol->setOffset(Vector3(-halfWidth - bufferSize / 2, 0, 0));
        // Right
        ColliderComponent* rightCol = new ColliderComponent(bufferSize, ARENA_HEIGHT);
        rightCol->setOffset(Vector3(halfWidth + bufferSize / 2, 0, 0));
        // Top
        ColliderComponent* topCol = new ColliderComponent(ARENA_HEIGHT, bufferSize);
        topCol->setOffset(Vector3(0, halfHeight + bufferSize / 2, 0));
        // Bottom
        ColliderComponent* bottomCol = new ColliderComponent(ARENA_HEIGHT, bufferSize);
        bottomCol->setOffset(Vector3(0, -halfHeight - bufferSize / 2, 0));

        entity->addComponent(leftCol);
        entity->addComponent(rightCol);
        entity->addComponent(topCol);
        entity->addComponent(bottomCol);

    }

    static Entity* getEntity() {
        Entity* arena = new Entity();

        MeshComponent* arenaMeshRender = new MeshComponent();
        arena->addComponent(arenaMeshRender);

        arena->addComponent(new WallScript());

        addColliders(arena);

        arena->setPosition(Vector3(0, 0, 0));

        return arena;
    }

    static void applyMasks(Scene* scene){

        float pad = 5;
        float dist = 100000;

        Mesh maskLeft;
        maskLeft.mode = GL_QUADS;
        maskLeft.colour = Vector3(0, 0, 0);
        maskLeft.data = {
                MeshData(-ARENA_WIDTH/2 - pad, -(ARENA_HEIGHT + dist)/2, 0),
                MeshData(-ARENA_WIDTH/2 - pad, (ARENA_HEIGHT + dist)/2, 0),
                MeshData(-dist, (ARENA_HEIGHT + dist)/2, 0),
                MeshData(-dist, -(ARENA_HEIGHT + dist)/2, 0)
        };

        Mesh maskRight;
        maskRight.mode = GL_QUADS;
        maskRight.colour = Vector3(0, 0, 0);
        maskRight.data = {
                MeshData(ARENA_WIDTH/2 + pad, (ARENA_HEIGHT + dist)/2, 0),
                MeshData(ARENA_WIDTH/2 + pad, -(ARENA_HEIGHT + dist)/2, 0),
                MeshData(dist, -(ARENA_HEIGHT + dist)/2, 0),
                MeshData(dist, (ARENA_HEIGHT + dist)/2, 0)
        };

        Mesh maskTop;
        maskTop.mode = GL_QUADS;
        maskTop.colour = Vector3(0, 0, 0);
        maskTop.data = {
                MeshData(-(ARENA_WIDTH + dist)/2, ARENA_HEIGHT/2 + pad, 0),
                MeshData((ARENA_WIDTH + dist)/2, ARENA_HEIGHT/2 + pad, 0),
                MeshData((ARENA_WIDTH + dist)/2, dist, 0),
                MeshData(-(ARENA_WIDTH + dist)/2, dist, 0)
        };

        Mesh maskBottom;
        maskBottom.mode = GL_QUADS;
        maskBottom.colour = Vector3(0, 0, 0);
        maskBottom.data = {
                MeshData((ARENA_WIDTH + dist)/2, -ARENA_HEIGHT/2 - pad, 0),
                MeshData(-(ARENA_WIDTH + dist)/2, -ARENA_HEIGHT/2 - pad, 0),
                MeshData(-(ARENA_WIDTH + dist)/2, -dist, 0),
                MeshData((ARENA_WIDTH + dist)/2, -dist, 0)
        };



        scene->masks.push_back(maskTop);
        scene->masks.push_back(maskBottom);
        scene->masks.push_back(maskLeft);
        scene->masks.push_back(maskRight);
}

};


#endif //I3D_ARENAENTITY_H
