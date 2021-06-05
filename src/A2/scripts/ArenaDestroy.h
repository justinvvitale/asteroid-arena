//
// Created by dim on 2/06/2021.
//

#ifndef I3D_ARENADESTROY_H
#define I3D_ARENADESTROY_H


#include "../../core/ecs/components/ScriptComponent.h"

class ArenaDestroy : public ScriptComponent {
private:
protected:
    void start() override;

    void update() override;
};


#endif //I3D_ARENADESTROY_H
