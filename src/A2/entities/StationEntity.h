//
// Created by dim on 21/04/2021.
//

#ifndef I3D_STATIONENTITY_H
#define I3D_STATIONENTITY_H

#include "../scripts/PlayerControllerScript.h"
#include "../scripts/TestScript.h"
#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../../core/external/ObjAccess.h"

class StationEntity {

public:

    static Entity* getEntity() {
        Entity* station = new Entity("station");
        station->setPosition(Vector3(0,0,-10));

        MeshComponent* meshComp = new MeshComponent();
        Mesh mesh = ObjAccess::load("outerStation");
        Renderer::loadTexture("metal", "data/metal.jpg");
        mesh.texture = "metal";
        meshComp->setMesh(mesh);
        station->addComponent(meshComp);

        RigidbodyComponent* rigid = new RigidbodyComponent();
        rigid->setSpin(Vector3(0.5,1,1));
        station->addComponent(rigid);

        // Setup inner section
        Entity* innerStation = new Entity();

        // Mesh
        MeshComponent* innerMeshComp = new MeshComponent();
        Mesh innerMesh = ObjAccess::load("innerStation");
        innerMesh.texture = "metal";
        innerMeshComp->setMesh(innerMesh);
        innerStation->addComponent(innerMeshComp);

        // Rigid
        RigidbodyComponent* innerRigid = new RigidbodyComponent();
        innerRigid->setSpin(Vector3(5,0,0));
        innerStation->addComponent(innerRigid);

        station->addChild(innerStation);




        return station;
    }
};

#endif //I3D_STATIONENTITY_H
