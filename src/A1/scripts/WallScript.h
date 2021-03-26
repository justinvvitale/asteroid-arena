//
// Created by dim on 23/03/2021.
//

#ifndef I3D_WALLSCRIPT_H
#define I3D_WALLSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"
#include "../../core/ecs/components/MeshComponent.h"

class WallScript : public ScriptComponent {
public:

private:
    void update() override;

    void start() override;

    void refreshMeshData();

public:
    void onCollision(Entity* other) override;

private:

    MeshComponent* meshComponent;

    Vector3 topLeftVert;
    Vector3 topRightVert;
    Vector3 bottomLeftVert;
    Vector3 bottomRightVert;

    bool topWarn = false;
    bool bottomWarn = false;
    bool leftWarn = false;
    bool rightWarn = false;


};


#endif //I3D_WALLSCRIPT_H
