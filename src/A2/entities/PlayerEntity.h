//
// Created by dim on 21/04/2021.
//

#ifndef I3D_PLAYERENTITY_H
#define I3D_PLAYERENTITY_H

#include "../../core/Renderer.h"
#include "../scripts/PlayerControllerScript.h"
#include "../../core/ecs/components/CameraComponent.h"
#include "../../core/external/ObjAccess.h"

class PlayerEntity {

public:
    static Entity* getEntity() {
        Entity* player = new Entity("player");

        CameraComponent* cameraComponent = new CameraComponent();
        cameraComponent->setCameraOffset(Vector3(0,2,10));

        PlayerControllerScript* controllerScript = new PlayerControllerScript();


        MeshComponent* meshComp = new MeshComponent();
        Mesh mesh = ObjAccess::load("ship");
        Renderer::loadTexture("ship", "data/ship.png");
        mesh.texture = "ship";
        meshComp->setMesh(mesh);

        player->addComponent(meshComp);
        player->addComponent(controllerScript);
        player->addComponent(cameraComponent);

        return player;
    }
};

#endif //I3D_PLAYERENTITY_H
