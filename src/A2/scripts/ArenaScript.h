//
// Created by dim on 23/03/2021.
//

#ifndef I3D_ARENASCRIPT_H
#define I3D_ARENASCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"
#include "../../core/ecs/components/MeshComponent.h"

class ArenaScript : public ScriptComponent {
private:
    void update() override;

    void start() override;

    CustomRenderMesh customRender;

public:

private:
    MeshComponent* meshComponent;
};


#endif //I3D_ARENASCRIPT_H
