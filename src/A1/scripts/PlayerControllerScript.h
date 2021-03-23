//
// Created by dim on 22/03/2021.
//

#ifndef I3D_PLAYERCONTROLLERSCRIPT_H
#define I3D_PLAYERCONTROLLERSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"

class PlayerControllerScript : ScriptComponent {
    float velocity = 0;

    void start() override;

    void update() override;

    void onCollision(Entity* other) override;
};


#endif //I3D_PLAYERCONTROLLERSCRIPT_H
