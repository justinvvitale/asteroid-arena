//
// Created by dim on 26/03/2021.
//

#ifndef I3D_BULLETENTITY_H
#define I3D_BULLETENTITY_H

#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../../core/ecs/components/ColliderComponent.h"

class BulletEntity {
private:
    static Mesh getModel() {
//        return MeshHelper::getHexagonMesh(10);
        Mesh mesh;
        mesh.mode = GL_POINTS;
        mesh.data = {
                MeshData(0, 0, 0),
        };

        return mesh;
    }

public:
    static Entity* getEntity(Vector3 initialPosition, Vector3 force) {
        Entity* entity = new Entity("bullet");

        entity->setPosition(initialPosition);

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getModel());
        entity->addComponent(meshRenderer);

        ColliderComponent* col = new ColliderComponent(POINT_SIZE);

        RigidbodyComponent* rb = new RigidbodyComponent();
        rb->addForce(force);

        entity->addComponent((Component*)rb);
        entity->addComponent((Component*) col);

        return entity;
    }

};

#endif //I3D_BULLETENTITY_H
