//
// Created by dim on 26/03/2021.
//

#ifndef I3D_BULLETENTITY_H
#define I3D_BULLETENTITY_H

#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../../core/Renderer.h"

class BulletEntity {
private:

public:
    static Entity* getEntity(Vector3 initialPosition, Vector3 force) {
        Entity* entity = new Entity("bullet");

        entity->setPosition(initialPosition);

        Renderer::loadTexture("bullet", "data/bullet.png");
        MeshComponent* meshRenderer = new MeshComponent(CustomRender::Bullet);
        entity->addComponent(meshRenderer);

        RigidbodyComponent* rb = new RigidbodyComponent();
        rb->addForce(force);

        entity->addComponent((Component*) rb);

        return entity;
    }

};

#endif //I3D_BULLETENTITY_H
