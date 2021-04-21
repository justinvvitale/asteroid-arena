//
// Created by dim on 22/03/2021.
//

#ifndef I3D_COLLISIONSYSTEM3D_H
#define I3D_COLLISIONSYSTEM3D_H


#include "../System.h"
#include "../components/ColliderComponent2D.h"
#include "../components/ColliderComponent3D.h"

class CollisionSystem3D : public System {
private:

public:
    CollisionSystem3D();

    Vector3 offset;

private:
    void init() override;

    void process(std::list<Component*> items) override;

    static bool isCollided(const ColliderComponent3D& col1, const ColliderComponent3D& col2);
};


#endif //I3D_COLLISIONSYSTEM3D_H
