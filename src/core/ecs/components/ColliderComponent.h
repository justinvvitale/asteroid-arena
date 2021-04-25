//
// Created by dim on 21/04/2021.
//

#ifndef I3D_COLLIDERCOMPONENT_H
#define I3D_COLLIDERCOMPONENT_H


#include "../../shared/engine_math.h"
#include "../Component.h"

enum ColliderType {
    cube
};


class ColliderComponent : public Component {
private:
    ColliderType type;

    Vector3 offset = Vector3::zero();

public:
    explicit ColliderComponent();

    ColliderType getCollisionType();

    void setOffset(Vector3 offsetIn);

    Vector3 getOffset();
};


#endif //I3D_COLLIDERCOMPONENT_H
