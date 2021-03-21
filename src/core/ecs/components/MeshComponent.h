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

    void setMesh(const struct Mesh& meshIn);
    void addMesh(const struct Mesh& meshIn);

private:
    std::list<struct Mesh> data = std::list<struct Mesh>();

    void tick() override;
};


#endif //I3D_MESHCOMPONENT_H
