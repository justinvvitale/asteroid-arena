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

};


#endif //I3D_ARENAENTITY_H
