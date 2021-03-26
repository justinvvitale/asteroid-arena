//
// Created by dim on 24/03/2021.
//

#ifndef I3D_ASTEROIDENTITY_H
#define I3D_ASTEROIDENTITY_H


#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../scripts/AsteroidScript.h"
#include "../../core/ecs/components/MeshComponent.h"
#include "../../core/ecs/components/ColliderComponent.h"
#include "../GAMECONFIG.h"

class AsteroidEntity {
private:
    static Mesh getAsteroidModel(float radius, float sections, float randRange) {
        Mesh mesh;
        mesh.mode = GL_POLYGON;
        mesh.colour = Vector3(0.3, 0.3, 0.3);

        for (int i = 0; i < 360; i += 360 / sections) {
            float pointRadius = getRandomNumber(radius, radius + randRange);

            mesh.data.emplace_back(cos(i * DEG_TO_RAD) * pointRadius, sin(i * DEG_TO_RAD) * pointRadius, 0);
        }

        return mesh;
    }

public:
    static Entity* getEntity(AsteroidWaveScript* waveMgr) {
        Entity* entity = new Entity();

        float radius = ASTEROID_MIN_RADIUS + (rand() % static_cast<int>(ASTEROID_MAX_RADIUS - ASTEROID_MIN_RADIUS + 1));

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getAsteroidModel(radius, getRandomNumber(ASTEROID_SEGMENTS_MIN, ASTEROID_SEGMENTS_MAX), ASTEROID_RADIUS_VARIATION_RANGE));
        entity->addComponent(meshRenderer);

        AsteroidScript* scriptComponent = new AsteroidScript(waveMgr, radius,
                                                             getRandomNumber(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED));
        entity->addComponent((Component*) scriptComponent);

        ColliderComponent* col = new ColliderComponent(radius);
        entity->addComponent((Component*) col);

        RigidbodyComponent* rb = new RigidbodyComponent();
        entity->addComponent((Component*) rb);

        return entity;
    }

};


#endif //I3D_ASTEROIDENTITY_H
