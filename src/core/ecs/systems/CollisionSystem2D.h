//
// Created by dim on 22/03/2021.
//

#ifndef I3D_COLLISIONSYSTEM2D_H
#define I3D_COLLISIONSYSTEM2D_H


#include "../System.h"
#include "../components/ColliderComponent2D.h"

class CollisionSystem2D : public System {
private:

public:
    CollisionSystem2D();

    Vector3 offset;

private:
    void init() override;

    void process(std::list<Component*> items) override;

    static bool isCollided(ColliderComponent2D col1, ColliderComponent2D col2);
};


#endif //I3D_COLLISIONSYSTEM2D_H
