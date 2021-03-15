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
    glBegin(mesh.mode);
    for(Vector3 vert : mesh.vertices){
        glVertex3f(vert.x, vert.y, vert.z);
    }
    glEnd();
}

void MeshComponent::setMesh(struct Mesh meshIn) {
    this->mesh = meshIn;
}
