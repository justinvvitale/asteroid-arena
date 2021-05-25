//
// Created by Dimme on 15/03/2021.
//

#ifndef I3D_ENGINE_GRAPHIC_H
#define I3D_ENGINE_GRAPHIC_H

#include "engine_math.h"
#include "../ENGINECONFIG.h"
#include <list>

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

typedef struct Vertex {
    Vector3 position;
    Vector3 texCoord;
    Vector3 normal;
} Vertex;

typedef struct Face {
    Vertex* vert1;
    Vertex* vert2;
    Vertex* vert3;

    void render() const{
        glVertex3f(vert1->position.x, vert1->position.y, vert1->position.z);
        glVertex3f(vert2->position.x, vert2->position.y, vert2->position.z);
        glVertex3f(vert3->position.x, vert3->position.y, vert3->position.z);
    }
} Face;

typedef struct Mesh {
    std::list<Vertex*> vertices = std::list<Vertex*>();
    std::list<Face> faces = std::list<Face>();
} Mesh;

class MeshHelper {
public:


};

#endif //I3D_ENGINE_GRAPHIC_H
