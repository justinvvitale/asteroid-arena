//
// Created by dim on 24/04/2021.
//

#ifndef I3D_CAMERACOMPONENT_H
#define I3D_CAMERACOMPONENT_H


#include "../Component.h"

class CameraComponent : public Component {
public:
    float camRot = 0.0f;
    Vector3 lookDirection = Vector3(0,0,-1.0f);

    // Camera offset relative to the parent entity
    Vector3 cameraOffset = Vector3(0, 1.0, 5.0);

    CameraComponent();
    ~CameraComponent();
    void tick() override;

    void render();

    Vector3 getDirectionVector();

    const Vector3& getCameraOffset() const;
    void setCameraOffset(const Vector3& offset);

};


#endif //I3D_CAMERACOMPONENT_H
