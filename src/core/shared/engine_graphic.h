//
// Created by Dimme on 15/03/2021.
//

#ifndef I3D_ENGINE_GRAPHIC_H
#define I3D_ENGINE_GRAPHIC_H

#include "engine_math.h"
#include <freeglut.h>
#include <list>

struct Mesh {
    GLenum mode = GL_TRIANGLES;
    std::list<Vector3> vertices = std::list<Vector3>();
};

#endif //I3D_ENGINE_GRAPHIC_H
