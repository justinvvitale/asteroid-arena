//
// Created by dim on 21/03/2021.
//

#ifndef I3D_TESTENTITY_H
#define I3D_TESTENTITY_H


#include "../../core/ecs/components/ColliderComponent.h"

class TestEntity {
private:
    static Mesh getModel() {
        Mesh mesh;
        mesh.mode = GL_LINE_LOOP;
        mesh.data = {
                MeshData(-100, -100, 0),
                MeshData(100, -100, 0),
                MeshData(100, 100, 0),
                MeshData(-100, 100, 0)
        };

        return mesh;
    }

public:
    static Entity* getEntity() {
        Entity* entity = new Entity();

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getModel());
        entity->addComponent(meshRenderer);

        ColliderComponent* col = new ColliderComponent(100, 200);
        col->setOffset(Vector3(100, 0, 0));

        entity->addComponent((Component*) col);

        return entity;
    }

};


#endif //I3D_TESTENTITY_H
