//
// Created by Dimme on 10/03/2021.
//

#include "MeshComponent.h"
#include "gl/GL.h"
MeshComponent::MeshComponent() : Component(ComponentType::Mesh) {

}

void MeshComponent::tick() {
    // Do nothing
}

void MeshComponent::render() {
    for(const struct Mesh& mesh : data) {

        glBegin(mesh.mode);

        for (MeshData meshData : mesh.data) {
            switch(meshData.dataType){
                case primitive:
                    glVertex3f(meshData.data.x, meshData.data.y, meshData.data.z);
                    break;
                case colour:
                    glColor3f(meshData.data.x, meshData.data.y, meshData.data.z);
                    break;
            }
        }
        glEnd();
    }
}

void MeshComponent::setMesh(const struct Mesh& meshIn) {
    this->data.clear();
    this->data.push_back(meshIn);
}

void MeshComponent::addMesh(const struct Mesh& meshIn) {
    this->data.push_back(meshIn);
}
