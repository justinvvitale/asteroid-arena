//
// Created by dim on 23/03/2021.
//
#include "Renderer.h"

#define STB_IMAGE_IMPLEMENTATION

#include "external/stb_image.h"

#if _WIN32

#   include <Windows.h>

#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else

#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>

#endif


bool Renderer::hasGlLoaded = false;
std::unordered_map<std::string, int> Renderer::textures = std::unordered_map<std::string, int>();
std::queue<std::pair<std::string, std::pair<std::string, bool>>> Renderer::textureLoadQueue = std::queue<std::pair<std::string, std::pair<std::string, bool>>>();


void Renderer::glInitialized() {
    hasGlLoaded = true;

    // Load textures which have been requested
    while (!textureLoadQueue.empty()) {
        std::pair<std::string, std::pair<std::string, bool>> request = textureLoadQueue.front();
        std::string name = request.first;
        std::string path = request.second.first;
        bool isTransparent = request.second.second;

        unsigned int id = loadTextureGl(path, isTransparent);

        std::cout << "Loaded texture " << name << " and assigned ID " << id << std::endl;

        textures[name] = id;

        textureLoadQueue.pop();
    }
}


void Renderer::renderMesh(const Mesh& mesh) {
    TextureStart(mesh.texture);
    glPushAttrib(GL_LIGHTING_BIT);

    for (const Face& face : mesh.faces) {
        switch (face.type) {
            case triangle:
                glBegin(GL_TRIANGLES);
                break;
            case quad:
                glBegin(GL_QUADS);
                break;
            default:
                glBegin(GL_LINES);
                break;
        }

        float amb[] = {mesh.ambient.x, mesh.ambient.y, mesh.ambient.z, mesh.ambient.w};
        float diff[] = {mesh.diffuse.x, mesh.diffuse.y, mesh.diffuse.z, mesh.diffuse.w};
        float spec[] = {mesh.specular.x, mesh.specular.y, mesh.specular.z, mesh.specular.w};
        glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, spec);

        glColor3f(face.colour.x, face.colour.y, face.colour.z);

        for (int i = 0; i < face.type; i++) {
            Vertex* vert = face.vertices[i];

            glTexCoord2f(vert->texCoord.x, vert->texCoord.y);
            glNormal3f(vert->normal.x, vert->normal.y, vert->normal.z);
            glVertex3f(vert->position.x, vert->position.y, vert->position.z);
        }

        glColor4f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z, 1);

        glEnd();
    }

    glPopAttrib();
    TextureEnd();
    glColor4f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z, 1);
}

void Renderer::TextureEnd() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Renderer::TextureStart(std::string name) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getTextureId(name));
}

void Renderer::renderParticle(const Particle* particle) {
    push();
        move(particle->position);
        drawTransparentQuad(particle->texture, particle->scale, Vector3::zero(), particle->colour);
    pop();
}

void Renderer::drawTransparentQuad(const std::string& texture, float size, Vector3 offset, Vector3 colour) {
    push();
        Entity* player = Game::getEntity("player");
        rotate(Rotation::LookRotation(player->getForwardVector().opposite()));

        glColor4f(colour.x, colour.y, colour.z,1);

        glAlphaFunc(GL_GREATER, 0.5);
        glEnable(GL_ALPHA_TEST);

        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, Renderer::getTextureId(texture));

        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0);
            glVertex2f(-size, size);
            glTexCoord2f(0.0, 0.0);
            glVertex2f(-size, -size);
            glTexCoord2f(1.0, 0.0);
            glVertex2f(size, -size);
            glTexCoord2f(1.0, 1.0);
            glVertex2f(size, size);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glDisable(GL_ALPHA_TEST);
    pop();

    glColor4f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z, 1);

}

void Renderer::renderText(TextOrigin origin, Vector3 offset, const std::string& text, float scale) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glOrtho(0, w, 0, h, -1, 1);
    glColor3f(UI_COLOUR.x, UI_COLOUR.y, UI_COLOUR.z);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    switch (origin) {
        case centre:
            Renderer::move(Vector3((float) w / 2, (float) h / 2, 0));
            break;
        case topLeft:
            Renderer::move(Vector3(0, (float) h, 0));
            break;
        case topRight:
            Renderer::move(Vector3((float) w, (float) h, 0));
            break;
        case bottomLeft:
            // This is the default
            break;
        case bottomRight:
            Renderer::move(Vector3((float) w, 0, 0));
            break;
    }

    // Account for different screen resolutions with offset
    float impactUnit = (float) h * (float) w / 100000;
    Renderer::move(Vector3(offset.x * impactUnit, offset.y * impactUnit, 0));
    Renderer::scale(scale * impactUnit / 40);

    for (char c : text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);

    glMatrixMode(GL_MODELVIEW);
}


void Renderer::drawCharacter(char chr) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, chr);
}

void Renderer::setColour(Vector3 colour) {
    glColor3f(colour.x, colour.y, colour.z);
}

void Renderer::move(Vector3 move) {
    glTranslatef(move.x, move.y, move.z);
}

void Renderer::rotate(Rotation rotation) {
    float* mat = rotation.ToRotationMatrix();
    glMultMatrixf(mat);

    delete[] mat;
}

void Renderer::push() {
    glPushMatrix();
}

void Renderer::pop() {
    glPopMatrix();
}

void Renderer::scale(Vector3 scale) {
    glScalef(scale.x, scale.y, scale.z);
}

void Renderer::scale(float scale) {
    Renderer::scale(Vector3(scale, scale, scale));
}


unsigned int Renderer::loadTextureGl(const std::string& file, bool isTransparent) {
    stbi_set_flip_vertically_on_load(true);
    int width, height, components;
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &components, isTransparent ? STBI_rgb_alpha : STBI_rgb);

    if (data == nullptr) {
        std::cout << "(Error) Unable to load texture: " + file << std::endl;
        return 0;
    }

    unsigned int id;

    glPushAttrib(GL_TEXTURE_BIT);
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, isTransparent ? GL_RGBA : GL_RGB, width, height, 0,
                 isTransparent ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glPopAttrib();

    return id;
}

void Renderer::renderCustom(CustomRender customRender, float param1, float param2, float param3, Vector3 colour) {
    switch (customRender) {
        case Sphere:
            gluSphere(gluNewQuadric(), param1, param2, param3);
            break;
        case WireSphere:
            glutWireSphere(param1, param2, param3);
            break;
        case Cube:
            glutSolidCube(param1);
            break;
        case Bullet:
            drawTransparentQuad("bullet", param1);
            break;
        case Arena: {
            float sizeH = ARENA_SIZE * 0.5f;
            float sizing = ARENA_SPACING;

            // Calculate distance for colours
            Vector3 playerPos = Vector3(param1, param2, param3);
            float halfArena = ARENA_SIZE / 2;

            float distTop = halfArena - playerPos.y;
            float distBottom = halfArena + playerPos.y;
            float distNear =  halfArena - playerPos.z;
            float distFar = halfArena + playerPos.z;
            float distLeft = halfArena + playerPos.x;
            float distRight = halfArena - playerPos.x;

            bool override = !Game::paused;
            bool warns[6] = {
                    override && distRight <= ARENA_WARN_DIST,
                    override && distLeft <= ARENA_WARN_DIST,
                    override && distTop <= ARENA_WARN_DIST,
                    override && distBottom <= ARENA_WARN_DIST,
                    override && distNear <= ARENA_WARN_DIST,
                    override && distFar <= ARENA_WARN_DIST,
            };

            glDisable(GL_LIGHTING);

            int index = 0;
            for(auto directionVector : VectorUtil::DirectionVectors()){
                push();

                // Set colour for warns
                if(warns[index]){
                    glColor3f(ARENA_WARN_COLOUR.x, ARENA_WARN_COLOUR.y, ARENA_WARN_COLOUR.z);
                }else{
                    glColor3f(ARENA_COLOUR.x, ARENA_COLOUR.y, ARENA_COLOUR.z);
                }

                // Rotation
                rotate(Rotation::FromEuler(directionVector.second * 90 * DEG_TO_RAD));

                // Move into position
                // I don't know why Far is so special, but it's inverted, I assumed its because of the axis origin.
                move(Vector3::forward() * (directionVector.first == Far ? -sizeH : sizeH));

                // Render mesh
                glBegin(GL_LINES);
                    // Horizontal lines
                    for(float x = -sizeH; x <= sizeH; x += sizing ){
                        glVertex3f(x, -sizeH, 0.0f);
                        glVertex3f(x, sizeH, 0.0f);
                    }

                    // Vertical lines
                    for(float y = -sizeH; y <= sizeH; y += sizing ){
                        glVertex3f(-sizeH, y, 0.0f);
                        glVertex3f(sizeH, y, 0.0f);
                    }
                glEnd();

                glColor3f(ARENA_COLOUR.x, ARENA_COLOUR.y, ARENA_COLOUR.z);
                pop();
                index++;
            }

            glEnable(GL_LIGHTING);
            glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);
        }
            break;
        default:
            break;
    }

}

void Renderer::loadTexture(const std::string& name, const std::string& path, bool isTransparent) {
    // Don't allow double loading
    if (textures.find(name) != textures.end())
        return;

    if (hasGlLoaded) {
        unsigned int id = loadTextureGl(path, isTransparent);
        std::cout << "Loaded texture " << name << " and assigned ID " << id << std::endl;
        textures[name] = id;
    } else {
        textureLoadQueue.emplace(std::pair<std::string, std::pair<std::string, bool>>(name, std::pair<std::string, bool>(path, isTransparent)));
    }
}

unsigned int Renderer::getTextureId(const std::string& name) {
    return textures[name];
}



