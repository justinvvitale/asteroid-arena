//
// Created by dim on 22/03/2021.
//

#ifndef I3D_PLAYERCONTROLLERSCRIPT_H
#define I3D_PLAYERCONTROLLERSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"
#include "../../core/ecs/components/ParticleEmitterComponent.h"

class PlayerControllerScript : ScriptComponent {
    float velocity = 0;
    int lastParticleEmit = -1;

    ParticleEmitterComponent* emitter;

    void start() override;

    void update() override;

    void onCollision(Entity* other) override;
};


#endif //I3D_PLAYERCONTROLLERSCRIPT_H
