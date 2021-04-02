//
// Created by dim on 23/03/2021.
//

#include "Renderer.h"

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

void Renderer::renderMeshData(const Mesh& mesh) {
    setColour(mesh.colour);

    glBegin(mesh.mode);

    for (MeshData meshData : mesh.data) {
        switch (meshData.dataType) {
            case primitive:
                glVertex3f(meshData.data.x, meshData.data.y, meshData.data.z);
                break;
            case colour:
                glColor3f(meshData.data.x, meshData.data.y, meshData.data.z);
                break;
        }
    }
    glEnd();

    setColour(DEFAULT_COLOUR);
}

void Renderer::renderParticle(const Particle* particle) {
    glPushMatrix();
    move(particle->position);
    scale(particle->scale);
    renderMeshData(particle->mesh);
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

void Renderer::renderText(const std::string& text, float scale) {
    Renderer::scale(scale);

    Renderer::push();
    for (char c : text){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }
    Renderer::pop();
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
    glRotatef(rotation.angle, rotation.x, rotation.y, rotation.z);
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




