//
// Created by dim on 27/05/2021.
//

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "ObjAccess.h"

// Only dealing with f*cking triangles.
Mesh ObjAccess::load(const std::string& name) {
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
            face.vertices[0] = mesh.vertices[shape.mesh.indices[i].vertex_index];
            face.vertices[1] = mesh.vertices[shape.mesh.indices[i + 1].vertex_index];
            face.vertices[2] = mesh.vertices[shape.mesh.indices[i + 2].vertex_index];

            face.normal = MeshHelper::calculateNormal(face);

            // Map texture coordinates to shape's vertexes
            if(shape.mesh.indices[i].texcoord_index >= 0){
                face.vertices[0]->texCoord = Vector2(attrib.texcoords[2 * size_t(shape.mesh.indices[i].texcoord_index) + 0],
                                               attrib.texcoords[2 * size_t(shape.mesh.indices[i].texcoord_index) + 1]);
            }
            if(shape.mesh.indices[i + 1].texcoord_index >= 0){
                face.vertices[1]->texCoord = Vector2(attrib.texcoords[2 * size_t(shape.mesh.indices[i + 1].texcoord_index) + 0],
                                               attrib.texcoords[2 * size_t(shape.mesh.indices[i + 1].texcoord_index) + 1]);
            }
            if(shape.mesh.indices[i + 2].texcoord_index >= 0){
                face.vertices[2]->texCoord = Vector2(attrib.texcoords[2 * size_t(shape.mesh.indices[i + 2].texcoord_index) + 0],
                                               attrib.texcoords[2 * size_t(shape.mesh.indices[i + 2].texcoord_index) + 1]);
            }

            mesh.faces.push_back(face);
        }
    }

    return mesh;
}

