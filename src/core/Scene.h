//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_SCENE_H
#define I3D_SCENE_H

#include <typeinfo>
#include <string>
#include <list>
#include <iostream>
#include "ecs/Entity.h"

class Scene {
private:
    std::list<Entity *> sceneEntities = std::list<Entity *>();

public:
    void addEntity(Entity *entity);

    void removeEntity(Entity *entity);



    // Searching

    // Gotta throw it here, templates funky
    template<class C>
    std::list<C *> findComponentsOfType() {
        std::list<C *> components = std::list<C *>();
        std::string target = typeid(C).name();

        for (Entity *entity : sceneEntities) {
            for (Component *component : entity->getComponents()) {

                C *casted = dynamic_cast<C *>(component);
                if (casted != 0) {
                    components.push_back(casted);
                }
            }
        }

        return components;
    };
};


#endif //I3D_SCENE_H
