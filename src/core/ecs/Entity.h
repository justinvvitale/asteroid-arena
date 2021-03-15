//
// Created by Dimme on 9/03/2021.
//

#ifndef I3D_ENTITY_H
#define I3D_ENTITY_H

#include <list>
#include "../shared/engine_math.h"
#include "Component.h"

class Entity {
private:
    Entity* parent = nullptr;

    std::list<Component *> components = std::list<Component *>();

    Vector3 position = Vector3::zero();
    Quaternion rotation = Quaternion::zero();
public:
    void tick();

    void addComponent(Component *component);

    std::list<Component *> getComponents();
    Component* getComponentOfType(ComponentType componentType);

    Entity* getParent();

    // Transform
    Vector3 getPosition() const;
    void setPosition(const Vector3 &pos);
    const Quaternion &getRotation() const;
    void setRotation(const Quaternion &rotation);
};


#endif //I3D_ENTITY_H
