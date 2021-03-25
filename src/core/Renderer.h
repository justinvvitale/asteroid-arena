//
// Created by dim on 23/03/2021.
//

#ifndef I3D_RENDERER_H
#define I3D_RENDERER_H

#include "shared/engine_graphic.h"
#include "ecs/components/ParticleEmitterComponent.h"

class Renderer {
public:
    static void renderMeshData(const Mesh& mesh);
    static void renderParticle(const Particle* particle);

    // State
    static void setColour(Vector3 colour);

    static void move(Vector3 move);
    static void scale(Vector3 scale);
    static void scale(float scale);
    static void rotate(Rotation rotation);

    static void push();
    static void pop();

    // Helpers (General)


    // Helpers (Drawing)
    static void drawCircle(float radius);
    static void drawRect(float height, float width);
};


#endif //I3D_RENDERER_H
