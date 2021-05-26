//
// Created by Dimme on 15/03/2021.
//
#ifndef I3D_ENGINE_GRAPHIC_H
#define I3D_ENGINE_GRAPHIC_H

#include "engine_math.h"
#include "../ENGINECONFIG.h"
#include <list>
#include <vector>

typedef struct Vertex {
    Vector3 position;
    Vector2 texCoord;
} Vertex;

typedef struct Face {
    Vertex* vert1;
    Vertex* vert2;
    Vertex* vert3;

    Vector3 normal;
} Face;

typedef struct Mesh {
    std::vector<Vertex*> vertices = std::vector<Vertex*>();
    std::list<Face> faces = std::list<Face>();
} Mesh;

class MeshHelper {
public:
    static Vector3 calculateNormal(Face face){

        Vector3 p1 = Vector3();
        Vector3 p2 = Vector3();
        p1.x = face.vert1->position.x - face.vert2->position.x;
        p1.y = face.vert1->position.y - face.vert2->position.y;
        p1.z = face.vert1->position.z - face.vert2->position.z;

        p2.x = face.vert1->position.x - face.vert3->position.x;
        p2.y = face.vert1->position.y - face.vert3->position.y;
        p2.z = face.vert1->position.z - face.vert3->position.z;

        // Cross
        Vector3 normal = VectorUtil::Cross(p1, p2);

        return normal;
    }


};

#endif //I3D_ENGINE_GRAPHIC_H
