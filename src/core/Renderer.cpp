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
    while(!textureLoadQueue.empty()){
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
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Renderer::getTextureId(mesh.texture));

    for (const Face& face : mesh.faces){
        switch(face.type){
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
        float diff[] = {mesh.diffuse.x, mesh.diffuse.y, mesh.diffuse.z, mesh.diffuse.w};;

        glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);

        glColor3f(face.colour.x, face.colour.y, face.colour.z);

        for(int i = 0; i < face.type; i++){
            Vertex* vert = face.vertices[i];

            glTexCoord2f(vert->texCoord.x, vert->texCoord.y);
            glNormal3f(vert->normal.x, vert->normal.y,vert->normal.z);
            glVertex3f(vert->position.x, vert->position.y, vert->position.z);
        }

        glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);

        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glColor3f(DEFAULT_COLOUR.x, DEFAULT_COLOUR.y, DEFAULT_COLOUR.z);

}

void Renderer::renderParticle(const Particle* particle) {
    glPushMatrix();
    move(particle->position);
    scale(particle->scale);
    renderMesh(particle->mesh);
    glPopMatrix();
}

void Renderer::drawTransparentQuad(const std::string& texture, float size, Vector3 offset) {
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Renderer::getTextureId(texture));
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2f(-size,size);
    glTexCoord2f(0.0, 0.0); glVertex2f(-size,-size);
    glTexCoord2f(1.0, 0.0); glVertex2f(size,-size);
    glTexCoord2f(1.0, 1.0); glVertex2f(size,size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
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

            switch(origin){
                case centre:
                    Renderer::move(Vector3((float)w/2, (float)h/2, 0));
                    break;
                case topLeft:
                    Renderer::move(Vector3(0, (float)h, 0));
                    break;
                case topRight:
                    Renderer::move(Vector3((float)w, (float)h, 0));
                    break;
                case bottomLeft:
                    // This is the default
                    break;
                case bottomRight:
                    Renderer::move(Vector3((float)w, 0, 0));
                    break;
            }

            // Account for different screen resolutions with offset
            float impactUnit = (float)h*(float)w / 100000;
            Renderer::move(Vector3(offset.x * impactUnit, offset.y *impactUnit, 0));
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

void Renderer::moveCamera(Vector3 position, Rotation rotation) {
//    Vector3 eye = position;
//    Vector3 center = rotation * Vector3::forward();
//    Vector3 up = rotation * Vector3::up();
//
//    gluLookAt(position.x, position.y, position.z,
//              center.x, center.y, center.z,
//              up.x, up.y, up.z);
}

unsigned int Renderer::loadTextureGl(const std::string& file) {
    stbi_set_flip_vertically_on_load(true);
    int width, height, components;
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &components, STBI_rgb_alpha);

    if(data == nullptr){
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
    glTexImage2D(GL_TEXTURE_2D, 0, components == 4 ? GL_RGBA : GL_RGB, width, height, 0, components == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glPopAttrib();

    return id;
}

void Renderer::renderCustom(CustomRender customRender, Vector3 colour) {
    switch (customRender) {
        case Sphere:
            gluSphere(gluNewQuadric(), 25,100,20);
            break;
        case Cube:
            glutSolidCube(25);
            break;
        case Bullet:
            drawTransparentQuad("bullet", 100);
            break;
        default:
            break;
    }

}

void Renderer::loadTexture(const std::string& name, const std::string& path) {
    // Don't allow double loading
    if (textures.find(name) != textures.end())
        return;

    if(hasGlLoaded){
        unsigned int id = loadTextureGl(path);
        std::cout << "Loaded texture " << name << " and assigned ID " << id << std::endl;
        textures[name] = id;
    }else{
        textureLoadQueue.emplace(std::pair<std::string, std::string>(name, path));
    }
}

unsigned int Renderer::getTextureId(const std::string& name) {
    return textures[name];
}



