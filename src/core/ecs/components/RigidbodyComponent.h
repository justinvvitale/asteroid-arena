//
// Created by dim on 24/03/2021.
//

#ifndef I3D_RIGIDBODYCOMPONENT_H
#define I3D_RIGIDBODYCOMPONENT_H


#include "../Component.h"

class RigidbodyComponent : public Component {
private:
    Vector3 velocity = Vector3::zero();
    float velRot = 0;

public:
    RigidbodyComponent();

    void tick() override;

    void addForce(float x, float y, float z);

    void setForceRot(float rot);

    void addForce(Vector3 force);

    void clearVelocity();
};


#endif //I3D_RIGIDBODYCOMPONENT_H
