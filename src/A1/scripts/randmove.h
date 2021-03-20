//
// Created by dim on 21/03/2021.
//

#ifndef I3D_RANDMOVE_H
#define I3D_RANDMOVE_H


#include "../../core/ecs/components/ScriptComponent.h"

class Entity;

class randmove : ScriptComponent {
    void start() override;

    void update() override;
};


#endif //I3D_RANDMOVE_H
