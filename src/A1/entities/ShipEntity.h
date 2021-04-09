//
// Created by dim on 21/03/2021.
//

#ifndef I3D_SHIPENTITY_H
#define I3D_SHIPENTITY_H

#include <freeglut.h>
#include "../GAMECONFIG.h"
#include "../scripts/PlayerControllerScript.h"
#include "../../core/ecs/components/ColliderComponent.h"
#include "../../core/Renderer.h"
#include "BulletEntity.h"

class ShipEntity {

public:
    static Entity* getEntity() {
        Entity* ship = new Entity("player");

        // Setting ship to bottom left, aiming towards top right
        ship->setPosition(Vector3(0,0,0));
        ship->setRotation(Rotation(0, 0, 1, -50));

        MeshComponent* meshRender = new MeshComponent();
        meshRender->addMesh(getModel(GL_LINE_LOOP, SHIP_COLOUR_OUTLINE));
        meshRender->addMesh(getModel(GL_TRIANGLE_STRIP, SHIP_COLOUR));

        // Define the particle emitter and move it into the exhaust area
        ParticleEmitterComponent* emitter = new ParticleEmitterComponent(-SHIP_SIZE / 4);

        // WEAPON SYSTEM
        Entity* test = BulletEntity::getEntity(Vector3::zero(), Vector3::zero());



        ship->addComponent(meshRender);
        ship->addComponent((Component*) new PlayerControllerScript());

        // Add some relaxed colliders, circle doesn't do it justice.
        ColliderComponent* col = new ColliderComponent(SHIP_SIZE * SHIP_COLLIDER_RELAX);
        col->setOffset(Vector3(0, SHIP_SIZE / 8, 0)); // Adjust it a little for better fit.

        ship->addComponent((Component*) col);
        ship->addComponent((Component*) emitter);

        return ship;
    }

    static Mesh getModel(GLenum mode, Vector3 colour) {
        Mesh mesh;

        float shipSize = SHIP_SIZE;
        mesh.mode = mode;
        mesh.data = {
                MeshData(MeshDataType::colour, colour),
                MeshData(0, -shipSize / 4, 0), // Bottom center
                MeshData(0, shipSize / 1, 0), // Top center
                MeshData(-shipSize / 2, -shipSize / 2, 0), // Bottom left

                MeshData(0, -shipSize / 4, 0), // Bottom center
                MeshData(0, shipSize, 0), // Top center
                MeshData(shipSize / 2, -shipSize / 2, 0), // Bottom right
                MeshData(MeshDataType::colour, 1, 1, 1)
        };

        return mesh;
    }
};


#endif //I3D_SHIPENTITY_H
