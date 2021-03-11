//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_MESHCOMPONENT_H
#define I3D_MESHCOMPONENT_H


#include "../Component.h"

class MeshComponent : public Component {
public:
    MeshComponent();

private:
    void tick() override;
    //virtual void render() = 0;
};


#endif //I3D_MESHCOMPONENT_H
