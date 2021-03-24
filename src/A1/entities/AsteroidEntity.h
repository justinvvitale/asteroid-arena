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
    static struct Mesh getAsteroidModel(float radius, float sections, float randRange) {
        struct Mesh mesh;
        mesh.mode = GL_LINE_LOOP;

        // TODO: Randomized appearance and make it not a circle (Part of later sections)

        for (int i = 0; i < 360; i += 360 / sections){
                double degInRad = i * 3.14159/180;

                float pointRadius = getRandomNumber(radius, radius + randRange);

                mesh.data.emplace_back(cos(degInRad)*pointRadius,sin(degInRad)*pointRadius, 0);
        }

        return mesh;
    }

public:
    static Entity* getEntity() {
        Entity* entity = new Entity();

        float radius = ASTEROID_MIN_RADIUS + (rand() % static_cast<int>(ASTEROID_MAX_RADIUS - ASTEROID_MIN_RADIUS + 1));

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getAsteroidModel(radius,ASTEROID_SEGMENTS,ASTEROID_RADIUS_VARIATION_RANGE));
        entity->addComponent(meshRenderer);

        AsteroidScript* scriptComponent = new AsteroidScript(radius, getRandomNumber(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED));
        entity->addComponent((Component*) scriptComponent);

        ColliderComponent* col = new ColliderComponent(radius);
        entity->addComponent((Component*) col);

        RigidbodyComponent* rb = new RigidbodyComponent();
        entity->addComponent((Component*) rb);

        return entity;
    }

};


#endif //I3D_ASTEROIDENTITY_H
