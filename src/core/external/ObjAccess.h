//
// Created by dim on 26/05/2021.
//

#include "../shared/engine_graphic.h"

#ifndef I3D_OBJACCESS_H
#define I3D_OBJACCESS_H

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

class ObjAccess {
public:
    static Mesh load(const std::string& name){
        Mesh mesh = Mesh();

        tinyobj::ObjReader reader;
        reader.ParseFromFile("data/" + name + ".obj");

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        // Load vertices
        for(int i = 0; i < attrib.vertices.size(); i += 3){ // 3 x y z
            Vertex* vert = new Vertex();

            vert->position = Vector3(attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2]);

            mesh.vertices.push_back(vert);
        }

        // Load faces
        for(tinyobj::shape_t shape : shapes){
            for(int i = 0; i < shape.mesh.indices.size(); i += 3){ // triangles only e.g 3
                Face face = Face();
                face.vert1 = mesh.vertices[shape.mesh.indices[i].vertex_index];
                face.vert2 = mesh.vertices[shape.mesh.indices[i + 1].vertex_index];
                face.vert3 = mesh.vertices[shape.mesh.indices[i + 2].vertex_index];

                face.normal = MeshHelper::calculateNormal(face);

                // Map texture coordinates to shape's vertexes
                if(shape.mesh.indices[i].texcoord_index >= 0){
                    face.vert1->texCoord = Vector2(attrib.texcoords[2 * size_t(shape.mesh.indices[i].texcoord_index) + 0],
                                                   attrib.texcoords[2 * size_t(shape.mesh.indices[i].texcoord_index) + 1]);
                }
                if(shape.mesh.indices[i + 1].texcoord_index >= 0){
                    face.vert2->texCoord = Vector2(attrib.texcoords[2 * size_t(shape.mesh.indices[i + 1].texcoord_index) + 0],
                                                   attrib.texcoords[2 * size_t(shape.mesh.indices[i + 1].texcoord_index) + 1]);
                }
                if(shape.mesh.indices[i + 2].texcoord_index >= 0){
                    face.vert3->texCoord = Vector2(attrib.texcoords[2 * size_t(shape.mesh.indices[i + 2].texcoord_index) + 0],
                                                   attrib.texcoords[2 * size_t(shape.mesh.indices[i + 2].texcoord_index) + 1]);
                }

                mesh.faces.push_back(face);
            }
        }

        return mesh;
    }
};


#endif //I3D_OBJACCESS_H
