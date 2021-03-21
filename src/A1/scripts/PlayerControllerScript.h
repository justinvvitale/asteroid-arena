//
// Created by dim on 22/03/2021.
//

#ifndef I3D_PLAYERCONTROLLERSCRIPT_H
#define I3D_PLAYERCONTROLLERSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"

class PlayerControllerScript : ScriptComponent{
        void start() override;

        void update() override;
};


#endif //I3D_PLAYERCONTROLLERSCRIPT_H
