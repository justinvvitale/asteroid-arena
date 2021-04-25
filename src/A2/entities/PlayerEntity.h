//
// Created by dim on 21/04/2021.
//

#ifndef I3D_PLAYERENTITY_H
#define I3D_PLAYERENTITY_H

#include "../../core/Renderer.h"
#include "../scripts/PlayerControllerScript.h"
#include "../../core/ecs/components/CameraComponent.h"

class PlayerEntity {

public:
    static Entity* getEntity() {
        Entity* player = new Entity("player");

        CameraComponent* cameraComponent = new CameraComponent();
        PlayerControllerScript* controllerScript = new PlayerControllerScript();

        player->addComponent(controllerScript);
        player->addComponent(cameraComponent);

        return player;
    }
};

#endif //I3D_PLAYERENTITY_H
