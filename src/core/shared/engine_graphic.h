//
// Created by Dimme on 15/03/2021.
//

#ifndef I3D_ENGINE_GRAPHIC_H
#define I3D_ENGINE_GRAPHIC_H

#include "engine_math.h"
#include "../ENGINECONFIG.h"
#include <freeglut.h>
#include <list>

enum MeshDataType{
    primitive,
    colour
};

struct MeshData{
    MeshDataType dataType;
    Vector3 data;

    MeshData(float x, float y, float z){
        this->dataType = MeshDataType::primitive;
        data = Vector3(x,y,z);
    }

    MeshData(Vector3 position){
        this->dataType = MeshDataType::primitive;
        data = position;
    }

    MeshData(MeshDataType dataType, float v1, float v2, float v3){
        this->dataType = dataType;
        data = Vector3(v1,v2,v3);
    }

    MeshData(MeshDataType dataType, Vector3 inVec){
        this->dataType = dataType;
        data = inVec;
    }
};

struct Mesh {
    GLenum mode = GL_TRIANGLES;
    Vector3 colour = DEFAULT_COLOUR;
    std::list<MeshData> data = std::list<MeshData>();
};

class MeshHelper {
public:
    static struct Mesh getCircleMesh(float radius, Vector3 colour = Vector3::identity()){
        struct Mesh mesh;
        mesh.mode = GL_LINE_LOOP;
        mesh.colour = colour;

        for (int i = 0; i < 360; i++){
            double degInRad = i * 3.14159/180;
            mesh.data.emplace_back(MeshData(cos(degInRad)*radius,sin(degInRad)*radius, 0));
        }

        return mesh;
    }

};

#endif //I3D_ENGINE_GRAPHIC_H
