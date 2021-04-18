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

enum MeshDataType {
    primitive,
    colour
};

typedef struct MeshData {
    MeshDataType dataType;
    Vector3 data;

    MeshData(float x, float y, float z) {
        this->dataType = MeshDataType::primitive;
        data = Vector3(x, y, z);
    }

    explicit MeshData(Vector3 position) {
        this->dataType = MeshDataType::primitive;
        data = position;
    }

    MeshData(MeshDataType dataType, float v1, float v2, float v3) {
        this->dataType = dataType;
        data = Vector3(v1, v2, v3);
    }

    MeshData(MeshDataType dataType, Vector3 inVec) {
        this->dataType = dataType;
        data = inVec;
    }
} MeshData;

typedef struct Mesh {
    GLenum mode = GL_TRIANGLES;
    Vector3 colour = DEFAULT_COLOUR;
    std::list<MeshData> data = std::list<MeshData>();
} Mesh;

class MeshHelper {
public:
    static Mesh getCircleMesh(float radius, Vector3 colour = Vector3::identity()) {
        Mesh mesh;
        mesh.mode = GL_LINE_LOOP;
        mesh.colour = colour;

        for (int i = 0; i < 360; i++) {
            mesh.data.emplace_back(MeshData((float)cos(i * DEG_TO_RAD) * radius, (float)sin(i * DEG_TO_RAD) * radius, 0));
        }

        return mesh;
    }

    static Mesh getHexagonMesh(float size, Vector3 colour = Vector3::identity()) {
        Mesh mesh;
        mesh.mode = GL_LINE_LOOP;
        mesh.colour = colour;

        mesh.data.emplace_back(MeshData(-size / 2, size, 0));
        mesh.data.emplace_back(MeshData(size / 2, size, 0));
        mesh.data.emplace_back(MeshData(size, 0, 0));
        mesh.data.emplace_back(MeshData(size / 2, -size, 0));
        mesh.data.emplace_back(MeshData(-size / 2, -size, 0));
        mesh.data.emplace_back(MeshData(-size, 0, 0));

        return mesh;
    }

    static Mesh getTriangleMesh(float size, Vector3 colour = Vector3::identity()) {
        Mesh mesh;
        mesh.mode = GL_LINE_LOOP;
        mesh.colour = colour;

        mesh.data.emplace_back(MeshData(0, size, 0));
        mesh.data.emplace_back(MeshData(-size, -size, 0));
        mesh.data.emplace_back(MeshData(size, -size, 0));


        return mesh;
    }

    static Mesh getPointMesh(float size) {
        Mesh mesh;
        mesh.mode = GL_POINTS;
        mesh.data.emplace_back(MeshData(0, 0, 0));

        return mesh;
    }

};

#endif //I3D_ENGINE_GRAPHIC_H
