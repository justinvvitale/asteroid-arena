//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_COMPONENT_H
#define I3D_COMPONENT_H

class Entity;

class Component {
private:
    Entity *parent = nullptr;
public:
    void setParent(Entity *entity);

    virtual void tick() = 0;
};


#endif //I3D_COMPONENT_H
