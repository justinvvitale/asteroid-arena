//
// Created by dim on 21/04/2021.
//

#ifndef I3D_CUBEENTITY_H
#define I3D_CUBEENTITY_H

#include "../../core/Renderer.h"
#include "../scripts/PlayerControllerScript.h"

class CubeEntity {

public:

    static Mesh getModel() {
        Mesh mesh;

        float cubeSize = 100;
        mesh.mode = GL_TRIANGLE_STRIP;
        mesh.data = {
                MeshData(-cubeSize, cubeSize, cubeSize),     // Front top-left
                MeshData(cubeSize, cubeSize, cubeSize),      // Front top-right
                MeshData(-cubeSize, -cubeSize, cubeSize),    // Front bottom-left
                MeshData(cubeSize, -cubeSize, cubeSize),     // Front bottom-right
                MeshData(cubeSize, -cubeSize, -cubeSize),    // Back bottom-right
                MeshData(cubeSize, cubeSize, cubeSize),      // Front top-right
                MeshData(cubeSize, cubeSize, -cubeSize),     // Back top-right
                MeshData(-cubeSize, cubeSize, cubeSize),     // Front top-left
                MeshData(-cubeSize, cubeSize, -cubeSize),    // Back top-left
                MeshData(-cubeSize, -cubeSize, cubeSize),    // Front bottom-left
                MeshData(-cubeSize, -cubeSize, -cubeSize),   // Back bottom-left
                MeshData(cubeSize, -cubeSize, -cubeSize),    // Back bottom-right
                MeshData(-cubeSize, cubeSize, -cubeSize),    // Back top-left
                MeshData(cubeSize, cubeSize, -cubeSize)      // Back top-right
        };

        return mesh;
    }

    static Entity* getEntity() {
        Entity* cube = new Entity();

        cube->setRotation(Rotation(40,40,0));

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getModel());
        cube->addComponent(meshRenderer);

        return cube;
    }
};

#endif //I3D_CUBEENTITY_H
