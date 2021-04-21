//
// Created by dim on 21/04/2021.
//

#ifndef I3D_PLAYERENTITY_H
#define I3D_PLAYERENTITY_H

#include "../../core/Renderer.h"
#include "../scripts/PlayerControllerScript.h"

class PlayerEntity {

public:

    static Mesh getModel() {
        Mesh mesh;

        float playerSize = 30;
        mesh.mode = GL_TRIANGLE_STRIP;
        mesh.data = {
                MeshData(-playerSize, playerSize, playerSize),     // Front top-left
                MeshData(playerSize, playerSize, playerSize),      // Front top-right
                MeshData(-playerSize, -playerSize, playerSize),    // Front bottom-left
                MeshData(playerSize, -playerSize, playerSize),     // Front bottom-right
                MeshData(playerSize, -playerSize, -playerSize),    // Back bottom-right
                MeshData(playerSize, playerSize, playerSize),      // Front top-right
                MeshData(playerSize, playerSize, -playerSize),     // Back top-right
                MeshData(-playerSize, playerSize, playerSize),     // Front top-left
                MeshData(-playerSize, playerSize, -playerSize),    // Back top-left
                MeshData(-playerSize, -playerSize, playerSize),    // Front bottom-left
                MeshData(-playerSize, -playerSize, -playerSize),   // Back bottom-left
                MeshData(playerSize, -playerSize, -playerSize),    // Back bottom-right
                MeshData(-playerSize, playerSize, -playerSize),    // Back top-left
                MeshData(playerSize, playerSize, -playerSize)      // Back top-right
        };

        return mesh;
    }

    static Entity* getEntity() {
        Entity* player = new Entity("player");

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getModel());
        player->addComponent(meshRenderer);

        PlayerControllerScript* controllerScript = new PlayerControllerScript();
        player->addComponent(controllerScript);

        return player;
    }
};

#endif //I3D_PLAYERENTITY_H
