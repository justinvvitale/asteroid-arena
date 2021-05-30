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
private:
    static bool hasGlLoaded;

    static std::unordered_map<std::string, int> textures;
    std::queue<std::pair<std::string, std::string>> static textureLoadQueue;

    static unsigned int loadTextureGl(const std::string& file);

public:
    // Admin

    static void glInitialized();

    // Rendering
    static bool drawParticles;

    static void renderMesh(const Mesh& mesh);

    static void renderCustom(CustomRender customRender, Vector3 colour = Vector3::identity());

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

    static unsigned int getTextureId(const std::string& name);
    static void loadTexture(const std::string& name, const std::string& path);

    // Helpers (Drawing)
    static void drawCharacter(char chr);

    static void drawTransparentQuad(const std::string& texture, float size, Vector3 offset = Vector3::zero());

    static void moveCamera(Vector3 position, Vector3 direction);
};


#endif //I3D_RENDERER_H
