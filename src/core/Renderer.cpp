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
std::queue<std::pair<std::string, std::string>> Renderer::textureLoadQueue = std::queue<std::pair<std::string, std::string>>();


void Renderer::glInitialized() {
    hasGlLoaded = true;

    // Load textures which have been requested
    while (!textureLoadQueue.empty()) {
        std::pair<std::string, std::string> request = textureLoadQueue.front();
        std::string name = request.first;
        std::string path = request.second;

        unsigned int id = loadTextureGl(request.second);

        std::cout << "Loaded texture " << name << " and assigned ID " << id << std::endl;

        textures[name] = id;

        textureLoadQueue.pop();
    }
}


void Renderer::renderMesh(const Mesh& mesh) {
    TextureStart(mesh.texture);

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

        glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);

        glColor3f(face.colour.x, face.colour.y, face.colour.z);

        for (int i = 0; i < face.type; i++) {
            Vertex* vert = face.vertices[i];

            glTexCoord2f(vert->texCoord.x, vert->texCoord.y);
            glNormal3f(vert->normal.x, vert->normal.y, vert->normal.z);
            glVertex3f(vert->position.x, vert->position.y, vert->position.z);
        }

        glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);

        glEnd();
    }

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
    glPushMatrix();
    move(particle->position);
    scale(particle->scale);
    renderMesh(particle->mesh);
    glPopMatrix();
}

void Renderer::drawTransparentQuad(const std::string& texture, float size, Vector3 offset) {
    push();
    Entity* player = Game::getEntity("player");
    rotate(Rotation::LookRotation(player->getForwardVector().opposite()));

    glColor4f(1,1,1,1);


    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
//    glDisable(GL_BLEND);

    glDisable(GL_ALPHA_TEST);

    pop();
}

void Renderer::renderText(TextOrigin origin, Vector3 offset, const std::string& text, float scale) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glOrtho(0, w, 0, h, -1, 1);

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
    glColor3f(1, 0, 0);

    for (char c : text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

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


unsigned int Renderer::loadTextureGl(const std::string& file) {
    stbi_set_flip_vertically_on_load(true);
    int width, height, components;
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &components, STBI_rgb_alpha);

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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, components == 4 ? GL_RGBA : GL_RGB, width, height, 0,
                 components == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
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
        case CustomSphere:{
            float radius = param1; // Radius
            int fidelity = param2; // More = less detail

            if (radius < 1 || fidelity < 1){
                break;
            }

            for (int i = 0; i < 90; i += fidelity) {
                float distance1 = radius * sin((PI * i) / 180);
                float distance2 = radius * sin((PI * (i + fidelity)) / 180);

                float dist1Sqrt = sqrt(radius * radius - distance1 * distance1);
                float dist2Sqrt = sqrt(radius * radius - distance2 * distance2);

                for (int j = 0; j < 360; j += fidelity) {
                    Vector3 point1;
                    Vector3 point2;
                    Vector3 point3;
                    Vector3 point4;

                    point1.x = dist1Sqrt * cos((2 * PI * j) / 360);
                    point1.y = dist1Sqrt * sin(2 * PI * j / 360);
                    point1.z = distance1;

                    point2.x = dist1Sqrt * cos(2 * PI * (j + fidelity) / 360);
                    point2.y = dist1Sqrt * sin(2 * PI * (j + fidelity) / 360);
                    point2.z = distance1;

                    point3.x = dist2Sqrt * cos(2 * PI * j / 360);
                    point3.y = dist2Sqrt * sin(2 * PI * j / 360);
                    point3.z = distance2;

                    point4.x = dist2Sqrt * cos(2 * PI * (j + fidelity) / 360);
                    point4.y = dist2Sqrt * sin(2 * PI * (j + fidelity) / 360);
                    point4.z = -distance2;

                    // First half of sphere
                    Vector3 normal = MeshHelper::calculateNormal(point2, point1, point3);

                    glNormal3f(normal.x, normal.y, normal.z);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(point1.x, point1.y, distance1);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(point2.x, point2.y, distance1);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(point4.x, point4.y, distance2);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(point3.x, point3.y, distance2);
                    glEnd();


                    // Second half of sphere
                    point1.z = -distance1;
                    point2.z = -distance1;

                    normal = MeshHelper::calculateNormal(point4, point1, point2);
                    glNormal3f(normal.x, normal.y, normal.z);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(point3.x, point3.y, -distance2);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(point4.x, point4.y, -distance2);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(point2.x, point2.y, -distance1);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(point1.x, point1.y, -distance1);
                    glEnd();
                }
            }
        }
            break;
        case Cube:
            glutSolidCube(param1);
            break;
        case Bullet:
            drawTransparentQuad("bullet", param1);
            break;
        default:
            break;
    }

}

void Renderer::loadTexture(const std::string& name, const std::string& path) {
    // Don't allow double loading
    if (textures.find(name) != textures.end())
        return;

    if (hasGlLoaded) {
        unsigned int id = loadTextureGl(path);
        std::cout << "Loaded texture " << name << " and assigned ID " << id << std::endl;
        textures[name] = id;
    } else {
        textureLoadQueue.emplace(std::pair<std::string, std::string>(name, path));
    }
}

unsigned int Renderer::getTextureId(const std::string& name) {
    return textures[name];
}



