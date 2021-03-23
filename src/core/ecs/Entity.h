//
// Created by Dimme on 9/03/2021.
//

#ifndef I3D_ENTITY_H
#define I3D_ENTITY_H

#include <list>
#include "../shared/engine_math.h"
#include "enums/ComponentType.h"
#include "enums/EntityTag.h"

class Component;

class Entity {
private:
    Entity* parent = nullptr;
    std::list<Entity *> children = std::list<Entity *>();

    EntityTag tag = EntityTag::None;

    std::list<Component *> components = std::list<Component *>();

    Vector3 position = Vector3::zero();
    Quaternion rotation = Quaternion::zero();
public:
    Entity() = default;
    Entity(EntityTag entityTag);

    void tick();

    void addComponent(Component *component);

    std::list<Component *> getComponents();
    Component* getComponentOfType(ComponentType componentType);
    std::list<Component *> getComponentsOfType(ComponentType componentType);

    // Sets the tag, can be used for lookups
    EntityTag getTag();

    void setParent(Entity* entity);
    Entity* getParent();
    std::list<Entity *> getChildren();

    // Transform
    Vector3 getPosition() const;
    void setPosition(const Vector3 &pos);
    const Quaternion &getRotation() const;
    void setRotation(const Quaternion &rotation);
};


#endif //I3D_ENTITY_H
