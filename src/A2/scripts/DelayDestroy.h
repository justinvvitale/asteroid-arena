//
// Created by dim on 2/06/2021.
//

#ifndef I3D_DELAYDESTROY_H
#define I3D_DELAYDESTROY_H


#include "../../core/ecs/components/ScriptComponent.h"

class DelayDestroy : public ScriptComponent {
private:
    float startMs;
    float fuse;

protected:
    void start() override;

    void update() override;

public:
    DelayDestroy(float fuseMs);
};


#endif //I3D_DELAYDESTROY_H
