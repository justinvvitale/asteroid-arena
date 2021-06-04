//
// Created by dim on 21/04/2021.
//

#ifndef I3D_PLAYERCONTROLLERSCRIPT_H
#define I3D_PLAYERCONTROLLERSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"
#include "../../core/ecs/components/ParticleEmitterComponent.h"

class PlayerControllerScript : public ScriptComponent {
private:
    int lastShoot = -1;
    float velocity = 0;

    CameraComponent* camera;

protected:
    void start() override;

    void update() override;

public:
    void onCollision(Entity* other) override;

public:

};


#endif //I3D_PLAYERCONTROLLERSCRIPT_H
