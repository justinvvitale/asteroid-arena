//
// Created by dim on 21/04/2021.
//

#ifndef I3D_COLLIDERCOMPONENT3D_H
#define I3D_COLLIDERCOMPONENT3D_H


#include "../../shared/engine_math.h"
#include "../Component.h"

enum ColliderType3D {
    cube
};


class ColliderComponent3D : public Component {
private:
    ColliderType3D type;

    Vector3 offset = Vector3::zero();

public:
    explicit ColliderComponent3D();

    ColliderType3D getCollisionType();

    void setOffset(Vector3 offsetIn);

    Vector3 getOffset();
};


#endif //I3D_COLLIDERCOMPONENT3D_H
