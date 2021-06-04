//
// Created by dim on 21/03/2021.
//

#ifndef I3D_ARENAENTITY_H
#define I3D_ARENAENTITY_H

#include "../GAMECONFIG.h"
#include "../../core/ecs/components/MeshComponent.h"
#include "../scripts/ArenaScript.h"

class ArenaEntity {
public:
    static Entity* getEntity() {
        Entity* arena = new Entity("arena");

        arena->addComponent(new MeshComponent());

        arena->addComponent(new ArenaScript());

        return arena;
    }
};


#endif //I3D_ARENAENTITY_H
