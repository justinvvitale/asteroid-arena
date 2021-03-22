//
// Created by dim on 21/03/2021.
//

#ifndef I3D_SHIPENTITY_H
#define I3D_SHIPENTITY_H

#include "../CONFIG.h"
#include "../scripts/PlayerControllerScript.h"
#include "../../core/ecs/components/ColliderComponent.h"

class ShipEntity {
private:
    static struct Mesh getModel(GLenum mode, Vector3 colour){
        struct Mesh mesh;

        float shipSize = SHIP_SIZE;
        mesh.mode = mode;
        mesh.data = {
                MeshData(MeshDataType::colour, colour),
                MeshData(0,-shipSize/4,0), // Bottom center
                MeshData(0,shipSize/1,0), // Top center
                MeshData(-shipSize/2,-shipSize/2,0), // Bottom left

                MeshData(0,-shipSize/4,0), // Bottom center
                MeshData(0,shipSize,0), // Top center
                MeshData(shipSize/2,-shipSize/2,0), // Bottom right
                MeshData(MeshDataType::colour, 1,1,1)
        };

        return mesh;
    }

public:
    static Entity* getEntity(){
        Entity* ship = new Entity();

        MeshComponent* meshRender = new MeshComponent();
            meshRender->addMesh(getModel(GL_LINE_LOOP, SHIP_COLOUR_OUTLINE));
            meshRender->addMesh(getModel(GL_TRIANGLE_STRIP, SHIP_COLOUR));


        ship->addComponent(meshRender);
        ship->addComponent((Component*)new PlayerControllerScript());

        ship->addComponent((Component*)new ColliderComponent(ColliderType::circlePos, SHIP_SIZE));


        ship->setPosition(Vector3(0, 500, 0));

        return ship;
    }

};


#endif //I3D_SHIPENTITY_H
