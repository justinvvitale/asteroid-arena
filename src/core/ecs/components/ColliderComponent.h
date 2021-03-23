//
// Created by dim on 22/03/2021.
//

#ifndef I3D_COLLIDERCOMPONENT_H
#define I3D_COLLIDERCOMPONENT_H

#include <tuple>
#include "../Component.h"

enum ColliderType{
    circlePos,
    square
};


class ColliderComponent : public Component {
    private:
        ColliderType type;

        Vector3 offset = Vector3::zero();

        float radius = 0;

        float width = 0;
        float height = 0;
    public:
        explicit ColliderComponent(float radius);
        ColliderComponent(float width, float height);

        ColliderType getCollisionType();

        void setOffset(Vector3 offsetIn);
        Vector3 getOffset();

        float getCircleRadius() const;
        std::tuple<float, float> getSquareDimension();
};


#endif //I3D_COLLIDERCOMPONENT_H
