//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_COMPONENT_H
#define I3D_COMPONENT_H

enum ComponentType {
    Mesh,

};

class Entity;

class Component {
private:
    const ComponentType type;
    Entity *parent = nullptr;
public:
    explicit Component(ComponentType type);

    void setParent(Entity *entity);

    virtual void tick() = 0;

    ComponentType getType();
};


#endif //I3D_COMPONENT_H
