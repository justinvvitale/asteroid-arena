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

void Renderer::renderMesh(const Mesh& mesh) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mesh.textureRef);

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
//        float amb[] = {0.2f, 0.2f, 0.2f, 1.0f};;
//        float diff[] = {0.2, 0.2, 0.2, 1.0};
//
//        glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
//        glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);

        glNormal3f(face.normal.x, face.normal.y, face.normal.z);
        glColor3f(face.colour.x, face.colour.y, face.colour.z);

        for(int i = 0; i < face.type; i++){
            Vertex* vert = face.vertices[i];

            glTexCoord2f(vert->texCoord.x, vert->texCoord.y);
            glVertex3f(vert->position.x, vert->position.y, vert->position.z);
        }

        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Renderer::renderParticle(const Particle* particle) {
    glPushMatrix();
    move(particle->position);
    scale(particle->scale);
    renderMesh(particle->mesh);
    glPopMatrix();
}

void Renderer::drawRect(float width, float height) {
    float heightHalf = height / 2;
    float widthHalf = width / 2;

    glBegin(GL_LINE_LOOP);
    glVertex2f(widthHalf, heightHalf);
    glVertex2f(-widthHalf, heightHalf);
    glVertex2f(-widthHalf, -heightHalf);
    glVertex2f(widthHalf, -heightHalf);
    glEnd();
}

void Renderer::drawRectSolid(float width, float height) {
    float heightHalf = height / 2;
    float widthHalf = width / 2;

    glBegin(GL_QUADS);
    glVertex2f(widthHalf, heightHalf);
    glVertex2f(-widthHalf, heightHalf);
    glVertex2f(-widthHalf, -heightHalf);
    glVertex2f(widthHalf, -heightHalf);
    glEnd();
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

void Renderer::drawCircle(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        glVertex2f(cos(i * DEG_TO_RAD) * radius, sin(i * DEG_TO_RAD) * radius);
    }
    glEnd();
}

void Renderer::setColour(Vector3 colour) {
    glColor3f(colour.x, colour.y, colour.z);
}

void Renderer::move(Vector3 move) {
    glTranslatef(move.x, move.y, move.z);
}

void Renderer::rotate(Rotation rotation) {
    glRotatef(rotation.x, 1, 0, 0);
    glRotatef(rotation.y, 0, 1, 0);
    glRotatef(rotation.z, 1, 0, 1);
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

void Renderer::moveCamera(Vector3 position, Vector3 direction) {
    gluLookAt(position.x, position.y, position.z,
              position.x + direction.x, position.y + direction.y, position.z + direction.z,
              0.0f, 1.0f, 0.0f);
}

unsigned int Renderer::loadTexture(const std::string& file) {
    int width, height, components;
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &components, STBI_rgb);

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glPopAttrib();

    return id;
}

void Renderer::renderCustom(CustomRender customRender, Vector3 colour) {
    switch (customRender) {
        case Sphere:
            gluSphere(gluNewQuadric(), 25,100,20);
            break;
        default:
            break;
    }

}



