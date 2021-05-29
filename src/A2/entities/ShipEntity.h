//
// Created by dim on 21/04/2021.
//

#ifndef I3D_SHIPENTITY_H
#define I3D_SHIPENTITY_H

#include "../../core/Renderer.h"
#include "../scripts/PlayerControllerScript.h"
#include "../../core/ecs/components/CameraComponent.h"
#include "../../core/external/ObjAccess.h"

class ShipEntity {

public:
    static Entity* getEntity() {
        Entity* ship = new Entity();

        MeshComponent* meshComp = new MeshComponent();

        Mesh mesh = ObjAccess::load("ship");
        mesh.texture = "data/brick.jpg";
        meshComp->setMesh(mesh);

        ship->addComponent(meshComp);

        return ship;
    }
};

#endif //
