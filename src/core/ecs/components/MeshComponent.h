//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_MESHCOMPONENT_H
#define I3D_MESHCOMPONENT_H

#include <vector>
#include "../Component.h"
#include "../../shared/engine_graphic.h"
#include "../../loader/ObjModel.h"

enum MeshType {
    None,
    Raw,
    Obj
};

class MeshComponent : public Component {
public:
    explicit MeshComponent();

    void render();

    void setRawMesh(const Mesh& meshIn);
    void setObjMesh(const std::string& objPath);

    void addRawMesh(const Mesh& meshIn);

    void setScale(float scale);

    Mesh getRawMesh();

    void reset();

    ~MeshComponent();

private:
    MeshType meshType = MeshType::None;
    float scale = 1;

    // Data
    ObjModel* objModel = nullptr;
    std::list<Mesh> data = std::list<Mesh>();

    void tick() override;
};


#endif //I3D_MESHCOMPONENT_H
