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
    Vector3 position = Vector3::zero();
    Vector3 normal = Vector3::identity();
    Vector2 texCoord = Vector2::zero();

} Vertex;

enum FaceType{
    triangle = 3,
    quad = 4
};

enum CustomRender{
    None,
    Sphere,
    WireSphere,
    Cube,
    Bullet,
    Arena
};

typedef struct Face {
    Vertex* vertices[4] = {};
    FaceType type;

    Vector3 colour = Vector3::identity();

    explicit Face(FaceType type = triangle){
        this->type = type;
    }
} Face;

typedef struct Mesh {
    std::vector<Vertex*> vertices = std::vector<Vertex*>();
    std::vector<Face> faces = std::vector<Face>();
    std::string texture;


    Vector4 ambient = Vector4(0,0,0,0);
    Vector4 diffuse = Vector4(0,0,0,0);
    Vector4 specular = Vector4(0,0,0,0);


} Mesh;

class MeshHelper {
public:
    static Vector3 calculateNormal(Vector3 p1, Vector3 p2, Vector3 p3){
        return VectorUtil::Cross(p2 - p1, p3 - p1);
    }


};

#endif //I3D_ENGINE_GRAPHIC_H
