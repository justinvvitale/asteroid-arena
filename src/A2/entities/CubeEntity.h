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
        mesh.mode = GL_QUAD_STRIP;
        mesh.data = {
                // Top face
                MeshData(-cubeSize, cubeSize, -cubeSize),
                MeshData(-cubeSize, cubeSize,  cubeSize),
                MeshData( cubeSize, cubeSize,  cubeSize),

                // Bottom face
                MeshData( cubeSize, -cubeSize,  cubeSize),
                MeshData(-cubeSize, -cubeSize,  cubeSize),
                MeshData(-cubeSize, -cubeSize, -cubeSize),
                MeshData( cubeSize, -cubeSize, -cubeSize),

                // Front face
                MeshData( cubeSize,  cubeSize, cubeSize),
                MeshData(-cubeSize,  cubeSize, cubeSize),
                MeshData(-cubeSize, -cubeSize, cubeSize),
                MeshData( cubeSize, -cubeSize, cubeSize),

                // Back face
                MeshData( cubeSize, -cubeSize, -cubeSize),
                MeshData(-cubeSize, -cubeSize, -cubeSize),
                MeshData(-cubeSize,  cubeSize, -cubeSize),
                MeshData( cubeSize,  cubeSize, -cubeSize),

                // Left face
                MeshData(-cubeSize,  cubeSize,  cubeSize),
                MeshData(-cubeSize,  cubeSize, -cubeSize),
                MeshData(-cubeSize, -cubeSize, -cubeSize),
                MeshData(-cubeSize, -cubeSize,  cubeSize),

                // Right face
                MeshData(cubeSize,  cubeSize, -cubeSize),
                MeshData(cubeSize,  cubeSize,  cubeSize),
                MeshData(cubeSize, -cubeSize,  cubeSize),
                MeshData(cubeSize, -cubeSize, -cubeSize),
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
