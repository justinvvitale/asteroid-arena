//
// Created by dim on 22/03/2021.
//

#ifndef I3D_COLLIDERCOMPONENT2D_H
#define I3D_COLLIDERCOMPONENT2D_H

#include <tuple>
#include "../Component.h"

enum ColliderType2D {
    circlePos,
    square
};


class ColliderComponent2D : public Component {
private:
    ColliderType2D type;

    Vector3 offset = Vector3::zero();

    float radius = 0;

    float width = 0;
    float height = 0;
public:
    explicit ColliderComponent2D(float radius);

    ColliderComponent2D(float width, float height);

    ColliderType2D getCollisionType();

    void setOffset(Vector3 offsetIn);

    Vector3 getOffset();

    float getCircleRadius() const;

    std::tuple<float, float> getSquareDimension();
};


#endif //I3D_COLLIDERCOMPONENT2D_H
