//
// Created by dim on 27/04/2021.
//

#ifndef I3D_TESTSCRIPT_H
#define I3D_TESTSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"

class TestScript: public ScriptComponent {
protected:
    void start() override;

    void update() override;
};


#endif //I3D_TESTSCRIPT_H
