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
        mesh.mode = ASTEROID_SOLID ? GL_POLYGON : GL_LINE_LOOP;
        mesh.colour = ASTEROID_COLOUR;

        for (int i = 0; i < 360; i += 360 / sections) {
            float pointRadius = getRandomNumber(radius, radius + randRange);

            mesh.data.emplace_back(cos(i * DEG_TO_RAD) * pointRadius, sin(i * DEG_TO_RAD) * pointRadius, 0);
        }

        return mesh;
    }

public:
    static Entity* getEntity(float radius) {
        Entity* entity = new Entity("asteroid");

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getAsteroidModel(radius, getRandomNumber(ASTEROID_SEGMENTS_MIN, ASTEROID_SEGMENTS_MAX), ASTEROID_RADIUS_VARIATION_RANGE));
        entity->addComponent(meshRenderer);

        ColliderComponent* col = new ColliderComponent(radius);
        entity->addComponent((Component*) col);

        RigidbodyComponent* rb = new RigidbodyComponent();
        entity->addComponent((Component*) rb);

        return entity;
    }

};


#endif //I3D_ASTEROIDENTITY_H
