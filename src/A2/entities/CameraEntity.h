//
// Created by dim on 31/05/2021.
//

#ifndef I3D_CAMERAENTITY_H
#define I3D_CAMERAENTITY_H

#include "../scripts/CameraControlScript.h"

class CameraEntity {

public:
    static Entity* getEntity() {
        Entity* cameraEnt = new Entity("camera");

        CameraComponent* cameraComponent = new CameraComponent();

        cameraEnt->addComponent(new CameraControlScript());

        cameraEnt->addComponent(cameraComponent);

        return cameraEnt;
    }
};

#endif //I3D_CAMERAENTITY_H
