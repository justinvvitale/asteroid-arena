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

enum FaceType{
    triangle = 3,
    quad = 4
};

typedef struct Face {
    Vertex* vertices[4] = {};
    FaceType type;

    Vector3 colour = Vector3::identity();

    Vector3 normal;

    explicit Face(FaceType type = triangle){
        this->type = type;
    }
} Face;

typedef struct Mesh {
    std::vector<Vertex*> vertices = std::vector<Vertex*>();
    std::vector<Face> faces = std::vector<Face>();
    unsigned int textureRef = 0;

    std::string texture;
} Mesh;

class MeshHelper {
public:
    static Vector3 calculateNormal(Face face){
        // Handle different vertices faces (Mostly just triangles, cbs with rest.
        switch(face.type){
            case triangle:
            case quad:
                return VectorUtil::Cross(face.vertices[1]->position - face.vertices[0]->position, face.vertices[2]->position - face.vertices[0]->position);
            default:
                return {};
        }
    }


};

#endif //I3D_ENGINE_GRAPHIC_H
