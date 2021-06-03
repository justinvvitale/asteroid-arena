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
    reader.ParseFromFile("data/model/" + name + ".obj");

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

// Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
            Face face = Face();

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                Vertex* vertex = new Vertex();
                face.vertices[v] = vertex;
                mesh.vertices.push_back(vertex);

                // Vertex position
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
                tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
                tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];
                vertex->position = Vector3(vx,vy,vz);

                // Normal check
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                    tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                    tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
                    vertex->normal = Vector3(nx,ny,nz);
                }

                // TexCord check
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
                    vertex->texCoord = Vector2(tx,ty);
                }

            }
            index_offset += fv;

            mesh.faces.push_back(face);
            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }

    return mesh;
}

