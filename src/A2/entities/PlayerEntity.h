//
// Created by dim on 21/04/2021.
//

#ifndef I3D_PLAYERENTITY_H
#define I3D_PLAYERENTITY_H

#include "../../core/Renderer.h"
#include "../scripts/PlayerControllerScript.h"
#include "../../core/ecs/components/CameraComponent.h"
#include "../../core/external/ObjAccess.h"
#include "ShipEntity.h"

class PlayerEntity {

public:
    static Entity* getEntity() {
        Entity* player = new Entity("player");

        CameraComponent* cameraComponent = new CameraComponent();
        PlayerControllerScript* controllerScript = new PlayerControllerScript();

        // Mesh is on a different inner-entity so we can move it
        Entity* ship = ShipEntity::getEntity();
        ship->setPosition(0,-5,-50);
        ship->setRotation(Rotation(0,180,0));
        player->addChild(ship);

        player->addComponent(controllerScript);
        player->addComponent(cameraComponent);

        return player;
    }
};

#endif //I3D_PLAYERENTITY_H
