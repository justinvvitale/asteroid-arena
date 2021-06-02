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
#include "../../core/ecs/components/ColliderComponent.h"

class AsteroidEntity {
            public:
            static Entity* getEntity() {
                Entity* entity = new Entity("asteroid");

                MeshComponent* meshRenderer = new MeshComponent(CustomRender::CustomSphere, "asteroid" + std::to_string(getRandomNumber(0,4)) + ".jpg");
                meshRenderer->setScale(30);
                entity->addComponent(meshRenderer);

                RigidbodyComponent* rb = new RigidbodyComponent();
                entity->addComponent((Component*) rb);

                entity->addComponent(new ColliderComponent(sphere, 35));

                return entity;
            }

        };


#endif //I3D_ASTEROIDENTITY_H
