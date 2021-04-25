//
// Created by dim on 22/03/2021.
//

#ifndef I3D_COLLISIONSYSTEM_H
#define I3D_COLLISIONSYSTEM_H


#include "../System.h"
#include "../components/ColliderComponent.h"

class CollisionSystem : public System {
private:

public:
    CollisionSystem();

    Vector3 offset;

private:
    void init() override;

    void process(std::list<Component*> items) override;

    static bool isCollided(const ColliderComponent& col1, const ColliderComponent& col2);
};


#endif //I3D_COLLISIONSYSTEM_H
