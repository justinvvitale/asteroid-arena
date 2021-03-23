//
// Created by Dimme on 10/03/2021.
//

#include "MeshComponent.h"
#include "../../Renderer.h"

MeshComponent::MeshComponent() : Component(ComponentType::Mesh) {

}

void MeshComponent::tick() {
    // Do nothing
}

void MeshComponent::render() {
    for(const struct Mesh& mesh : data) {
        Renderer::renderMeshData(mesh);
    }
}

void MeshComponent::setMesh(const struct Mesh& meshIn) {
    this->data.clear();
    this->data.push_back(meshIn);
}

void MeshComponent::addMesh(const struct Mesh& meshIn) {
    this->data.push_back(meshIn);
}
