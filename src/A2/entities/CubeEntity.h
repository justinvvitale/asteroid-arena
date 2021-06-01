//
// Created by dim on 21/04/2021.
//

#ifndef I3D_CUBEENTITY_H
#define I3D_CUBEENTITY_H

#include "../scripts/PlayerControllerScript.h"
#include "../scripts/TestScript.h"
#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../../core/external/ObjAccess.h"

class CubeEntity {

public:

    static Entity* getEntity() {
        Entity* cube = new Entity("test");
        cube->setPosition(Vector3(0,0,-10));

        MeshComponent* meshComp = new MeshComponent(Cube);
        meshComp->setScale(100);

        cube->addComponent(new TestScript());
        cube->addComponent(meshComp);

        return cube;
    }
};

#endif //I3D_CUBEENTITY_H
//        Vertex* p1 = new Vertex();
//        Vertex* p2 = new Vertex();
//        Vertex* p3 = new Vertex();
//        p1->position = Vector3(0,1,0);
//        p2->position = Vector3(-1,0,0);
//        p3->position = Vector3(0,0,1);
//
//        Face face = Face();
//        face.vert1 = p1;
//        face.vert2 = p2;
//        face.vert3 = p3;
//
//        mesh.vertices.push_back(p1);
//        mesh.vertices.push_back(p2);
//        mesh.vertices.push_back(p3);
//
//        mesh.faces.push_back(face);