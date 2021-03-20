//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_COMPONENT_H
#define I3D_COMPONENT_H

#include "ComponentType.h"
#include "Entity.h"

class Component {
private:
    const ComponentType type;
    Entity* parent = nullptr;
public:
    explicit Component(ComponentType type);

    void setParent(Entity* entity);
    Entity* getParent();

    virtual void tick() = 0;

    ComponentType getType();
};


#endif //I3D_COMPONENT_H
