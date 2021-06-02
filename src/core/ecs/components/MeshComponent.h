//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_MESHCOMPONENT_H
#define I3D_MESHCOMPONENT_H

#include <utility>
#include <vector>
#include "../Component.h"
#include "../../shared/engine_graphic.h"

typedef struct CustomRenderMesh {
    CustomRender customRender = Sphere;
    std::string texture;
    float param1 = 0;
    float param2 = 0;
    float param3 = 0;

    CustomRenderMesh() {

    }

    explicit CustomRenderMesh(CustomRender customRender, std::string  texture = "", float param1 = 0, float param2 = 0, float param3 = 0)
            : customRender(customRender), texture(std::move(texture)), param1(param1), param2(param2), param3(param3) {}
} CustomRenderMesh;

class MeshComponent : public Component {
public:
    explicit MeshComponent();
    explicit MeshComponent(CustomRenderMesh customRenderMesh);

    void render();

    void setMesh(const Mesh& meshIn);

    void setScale(float scale);

    Mesh getMesh();


    void reset();

    ~MeshComponent();

private:
    float scale = 1;
    bool isCustomRender = false;
    CustomRenderMesh customRenderMesh;

    // Data
    Mesh mesh;

    void tick() override;
};


#endif //I3D_MESHCOMPONENT_H
