//
// Created by dim on 21/04/2021.
//

#ifndef I3D_CUBEENTITY_H
#define I3D_CUBEENTITY_H

#include "../../core/Renderer.h"
#include "../scripts/PlayerControllerScript.h"
#include "../scripts/TestScript.h"

class CubeEntity {

public:

    static Entity* getEntity() {
        Entity* cube = new Entity();

        //cube->setRotation(Rotation(40,40,0));

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setScale(1.2);
        meshRenderer->setObjMesh("data/test.obj");
        cube->addComponent(meshRenderer);

        cube->addComponent(new TestScript());

        return cube;
    }
};

#endif //I3D_CUBEENTITY_H
