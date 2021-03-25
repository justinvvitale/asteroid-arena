//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_SCRIPTCOMPONENT_H
#define I3D_SCRIPTCOMPONENT_H


#include "../Component.h"

class ScriptComponent : public Component {
private:
    bool hasInit = false;

protected:
    virtual void start() = 0;

    virtual void update() = 0;;

public:
    ScriptComponent();

    void tick() override;

    virtual void onCollision(Entity* other) {}
};


#endif //I3D_SCRIPTCOMPONENT_H
