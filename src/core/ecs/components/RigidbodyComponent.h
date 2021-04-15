//
// Created by dim on 24/03/2021.
//

#ifndef I3D_RIGIDBODYCOMPONENT_H
#define I3D_RIGIDBODYCOMPONENT_H


#include "../Component.h"

class RigidbodyComponent : public Component {
private:
    Vector3 velocity = Vector3::zero();
    float spin = 0;

public:
    RigidbodyComponent();

    void tick() override;

    void addForce(float x, float y, float z);

    void setSpin(float amount);

    void addForce(Vector3 force);

    Vector3 getVelocity();

    void clearVelocity();

    float getSpin() const;
};


#endif //I3D_RIGIDBODYCOMPONENT_H
