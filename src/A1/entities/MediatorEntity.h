//
// Created by Justin on 3/04/2021.
//

#ifndef I3D_MEDIATORENTITY_H
#define I3D_MEDIATORENTITY_H


#include "../scripts/MediatorScript.h"

class MediatorEntity {
    public:

        static Entity* getEntity() {
            Entity* entity = new Entity();

            MeshComponent* meshRenderer = new MeshComponent();

            entity->addComponent((Component*)meshRenderer);
            entity->addComponent((Component*) new MediatorScript());

            return entity;
        }
};


#endif //I3D_MEDIATORENTITY_H
