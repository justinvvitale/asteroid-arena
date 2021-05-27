//
// Created by dim on 23/03/2021.
//

#ifndef I3D_RENDERER_H
#define I3D_RENDERER_H

#include "shared/engine_graphic.h"
#include "ecs/components/ParticleEmitterComponent.h"

enum TextOrigin {
    centre,
    topLeft,
    topRight,
    bottomLeft,
    bottomRight
};

class Renderer {
public:
    static bool drawParticles;

    static void renderMesh(const Mesh& mesh);

    static void renderParticle(const Particle* particle);

    static void renderText(TextOrigin origin, Vector3 offset, const std::string& text, float scale = 1);

    // State
    static void setColour(Vector3 colour);

    static void move(Vector3 move);

    static void scale(Vector3 scale);

    static void scale(float scale);

    static void rotate(Rotation rotation);

    static void push();

    static void pop();

    // Helpers (General)

    static unsigned int loadTexture(const std::string& file);

    // Helpers (Drawing)
    static void drawCharacter(char chr);

    static void drawCircle(float radius);

    static void drawRect(float height, float width);

    static void drawRectSolid(float width, float height);

    static void moveCamera(Vector3 position, Vector3 direction);
};


#endif //I3D_RENDERER_H
