//
// Created by dim on 24/04/2021.
//

#ifndef I3D_CAMERACOMPONENT_H
#define I3D_CAMERACOMPONENT_H


#include "../Component.h"

class CameraComponent : public Component {
public:
    CameraComponent();
    ~CameraComponent();
    void tick() override;

    void render();

    Vector3 getDirectionVector();
};


#endif //I3D_CAMERACOMPONENT_H
