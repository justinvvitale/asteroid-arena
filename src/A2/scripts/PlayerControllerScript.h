//
// Created by dim on 21/04/2021.
//

#ifndef I3D_PLAYERCONTROLLERSCRIPT_H
#define I3D_PLAYERCONTROLLERSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"

class PlayerControllerScript : public ScriptComponent {
private:
    Vector3 cameraPos = Vector3(0,0,0);
    void updateCamera() const;

protected:
    void start() override;

    void update() override;

public:

};


#endif //I3D_PLAYERCONTROLLERSCRIPT_H
