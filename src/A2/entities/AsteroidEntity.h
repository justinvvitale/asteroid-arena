//
// Created by dim on 24/03/2021.
//

#ifndef I3D_ASTEROIDENTITY_H
#define I3D_ASTEROIDENTITY_H


#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../scripts/AsteroidScript.h"
#include "../../core/ecs/components/MeshComponent.h"
#include "../GAMECONFIG.h"
#include "../../core/external/ObjAccess.h"
#include "../../core/ecs/components/ColliderComponent.h"

class AsteroidEntity {

public:

    // Assisted by  http://songho.ca/opengl/gl_sphere.html
    static Mesh getModel(float radius, float stackCount, float sectorCount, std::string texture) {
        Mesh mesh = Mesh();

        // Temp vars
        float curZ, xy;
        // Normal var
        float length = 1.0f / radius;

        float sectorStep = 2 * PI / sectorCount;
        float stackStep = PI / stackCount;
        float sectorAngle, stackAngle;

        for(int i = 0; i <= stackCount; ++i){
            stackAngle = PI / 2 - i * stackStep;
            xy = radius * cosf(stackAngle);
            curZ = radius * sinf(stackAngle);

            for(int j = 0; j <= sectorCount; ++j){
                sectorAngle = j * sectorStep;

                Vertex* vert = new Vertex();

                // vertex position (x, y, curZ)
                vert->position.x = xy * cosf(sectorAngle);
                vert->position.y = xy * sinf(sectorAngle);
                vert->position.z = curZ;

                // Normals
                vert->normal.x = vert->position.x * length;
                vert->normal.y = vert->position.y * length;
                vert->normal.z = curZ * length;

                // Tex coordinates
                vert->texCoord.x = (float)j / sectorCount;
                vert->texCoord.y = (float)i / stackCount;

                mesh.vertices.push_back(vert);
            }
        }

        int curStack, nextStack;
        for(int i = 0; i < stackCount; ++i)
        {
            curStack = i * (sectorCount + 1);
            nextStack = curStack + sectorCount + 1;

            for(int j = 0; j < sectorCount; ++j, ++curStack, ++nextStack){

                // Special case for pivot points
                if(i != 0){
                    Face face = Face();
                    face.vertices[0] = mesh.vertices[curStack];
                    face.vertices[1] = mesh.vertices[nextStack];
                    face.vertices[2] = mesh.vertices[curStack + 1];

                    mesh.faces.push_back(face);
                }

                if(i != (stackCount-1)){
                    Face face = Face();
                    face.vertices[0] = mesh.vertices[curStack + 1];
                    face.vertices[1] = mesh.vertices[nextStack];
                    face.vertices[2] = mesh.vertices[nextStack + 1];

                    mesh.faces.push_back(face);
                }
            }
        }

        mesh.texture = texture;
        // Show a specular highlight.
        mesh.specular = Vector4(0.2,0.2,0.2,1);

        return mesh;
    }

    static Entity* getEntity() {
        Entity* entity = new Entity("asteroid");

        RigidbodyComponent* rb = new RigidbodyComponent();
        entity->addComponent((Component*) rb);

        return entity;
    }

};

#endif //I3D_ASTEROIDENTITY_H
