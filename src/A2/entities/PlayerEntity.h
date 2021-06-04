//
// Created by dim on 21/04/2021.
//

#ifndef I3D_PLAYERENTITY_H
#define I3D_PLAYERENTITY_H

#include "../../core/Renderer.h"
#include "../scripts/PlayerControllerScript.h"
#include "../../core/ecs/components/CameraComponent.h"
#include "../../core/external/ObjAccess.h"
#include "../../core/ecs/components/ColliderComponent.h"
#include "../GAMECONFIG.h"

class PlayerEntity {

public:
    static Entity* getEntity() {
        Entity* player = new Entity("player");

        PlayerControllerScript* controllerScript = new PlayerControllerScript();

        MeshComponent* meshComp = new MeshComponent();
        Mesh mesh = ObjAccess::load("ship");
        Renderer::loadTexture("ship", "data/texture/ship.png");
        mesh.texture = "ship";
        meshComp->setMesh(mesh);

        player->addComponent(new ColliderComponent( sphere, SHIP_COLLIDER_SIZE));

        // exhausts (Not used but required for other particles)
        player->addComponent(new ParticleEmitterComponent(Vector3(0,0,-1)));


        player->addComponent(controllerScript);
        player->addComponent(meshComp);
        return player;
    }
};

#endif //I3D_PLAYERENTITY_H
