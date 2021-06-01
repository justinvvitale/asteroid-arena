//
// Created by dim on 1/06/2021.
//

#ifndef I3D_CAMERAENTITY_H
#define I3D_CAMERAENTITY_H

class CameraEntity {

public:
    static Entity* getEntity() {
        Entity* camera = new Entity();

        CameraComponent* cameraComponent = new CameraComponent();

        camera->addComponent(cameraComponent);
        return camera;
    }
};

#endif //I3D_CAMERAENTITY_H
