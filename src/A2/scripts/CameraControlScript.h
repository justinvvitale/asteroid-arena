//
// Created by dim on 31/05/2021.
//

#ifndef I3D_CAMERACONTROLSCRIPT_H
#define I3D_CAMERACONTROLSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"
#include "../../core/ecs/components/CameraComponent.h"

class CameraControlScript : public ScriptComponent {
private:
    CameraComponent* cam;
    Entity* player;

    float velocity = 0;
protected:
    void start() override;

    void update() override;
};


#endif //I3D_CAMERACONTROLSCRIPT_H
