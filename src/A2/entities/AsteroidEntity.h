//
// Created by dim on 24/03/2021.
//

#ifndef I3D_ASTEROIDENTITY_H
#define I3D_ASTEROIDENTITY_H


#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../scripts/AsteroidScript.h"
#include "../../core/ecs/components/MeshComponent.h"
#include "../GAMECONFIG.h"
#include "../../core/external/ObjAccess.h"

class AsteroidEntity {
private:
    static Mesh getAsteroidModel(float radius, int stacks, int slices) {
                Mesh mesh = ObjAccess::load("ship");

                return mesh;
            }

            public:
            static Entity* getEntity(float radius) {
                Entity* entity = new Entity("asteroid");

                MeshComponent* meshRenderer = new MeshComponent();
                meshRenderer->setMesh(
                        getAsteroidModel(radius, getRandomNumber(ASTEROID_SEGMENTS_MIN, ASTEROID_SEGMENTS_MAX),
                                         ASTEROID_RADIUS_VARIATION_RANGE));
                entity->addComponent(meshRenderer);

                RigidbodyComponent* rb = new RigidbodyComponent();
                entity->addComponent((Component*) rb);

                return entity;
            }

        };


#endif //I3D_ASTEROIDENTITY_H
