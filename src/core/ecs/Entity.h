//
// Created by Dimme on 9/03/2021.
//

#ifndef I3D_ENTITY_H
#define I3D_ENTITY_H

#include <list>
#include <string>
#include "../shared/engine_math.h"
#include "enums/ComponentType.h"

class Component;

class Entity {
private:
    Entity* parent = nullptr;
    std::list<Entity*> children = std::list<Entity*>();

    std::string tag;

    std::list<Component*> components = std::list<Component*>();

    Vector3 position = Vector3::zero();
    Rotation rotation = Rotation::zero();
public:
    Entity() = default;

    explicit Entity(std::string tag);

    void tick();

    void addComponent(Component* component);

    void removeComponent(Component* component);

    std::list<Component*> getComponents();

    Component* getComponentOfType(ComponentType componentType);

    Component* getComponentOfTypeInChildren(ComponentType componentType);

    std::list<Component*> getComponentsOfType(ComponentType componentType);

    // Sets the tag, can be used for lookups
    std::string getTag();

    void setParent(Entity* entity);

    Entity* getParent();

    std::list<Entity*> getChildren();

    void addChild(Entity* entity);

    void removeChild(Entity* entity);

    // Transform
    Vector3 getPosition() const;

    Vector3 getWorldPosition();

    void setPosition(const Vector3& pos);

    Rotation getRotation() const;

    void destroy();

    virtual ~Entity();

    void setRotation(const Rotation& rotation);
};


#endif //I3D_ENTITY_H
