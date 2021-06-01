//
// Created by dim on 24/04/2021.
//

#ifndef I3D_CAMERACOMPONENT_H
#define I3D_CAMERACOMPONENT_H


#include "../Component.h"
#include "MeshComponent.h"

class CameraComponent : public Component {
public:
    CameraComponent();
    ~CameraComponent();
    void tick() override;

    MeshComponent* meshComponent;

    Rotation rotOffset = Rotation::identity();
    Vector3 posOffset = Vector3::zero();

    void render();

    Vector3 getDirectionVector();
};


#endif //I3D_CAMERACOMPONENT_H
