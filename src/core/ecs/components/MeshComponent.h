//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_MESHCOMPONENT_H
#define I3D_MESHCOMPONENT_H

#include <vector>
#include "../Component.h"
#include "../../shared/engine_graphic.h"


class MeshComponent : public Component {
public:
    MeshComponent();

    void render();

    void setMesh(const Mesh& meshIn);

    void addMesh(const Mesh& meshIn);

private:
    std::list<Mesh> data = std::list<Mesh>();

    void tick() override;
};


#endif //I3D_MESHCOMPONENT_H
