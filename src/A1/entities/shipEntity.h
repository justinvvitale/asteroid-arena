//
// Created by dim on 21/03/2021.
//

#ifndef I3D_SHIPENTITY_H
#define I3D_SHIPENTITY_H


#include "../scripts/randmove.h"

class ShipEntity {
private:
    static struct Mesh getModel(){
        struct Mesh mesh;
        mesh.mode = GL_LINE_LOOP;
        mesh.vertices = {
                Vector3(-100,-100,0),
                Vector3(100,-100,0),
                Vector3(100,100,0),
                Vector3(-100,100,0)
        };

        return mesh;
    }

public:
    static Entity* getEntity(){
        Entity* ship = new Entity();

        MeshComponent* meshRender = new MeshComponent();
            meshRender->setMesh(getModel());
        ship->addComponent(meshRender);
        ship->addComponent((Component*)new randmove());

        ship->setPosition(Vector3(0, 500, 0));

        return ship;
    }

};


#endif //I3D_SHIPENTITY_H
