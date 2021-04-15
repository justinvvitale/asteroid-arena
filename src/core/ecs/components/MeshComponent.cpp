//
// Created by Dimme on 10/03/2021.
//

#include "MeshComponent.h"
#include "../../Renderer.h"

MeshComponent::MeshComponent() : Component(ComponentType::CMesh) {

}

void MeshComponent::tick() {
    // Do nothing
}

void MeshComponent::render() {
    for (const Mesh& mesh : data) {
        Renderer::renderMeshData(mesh);
    }
}

void MeshComponent::setMesh(const Mesh& meshIn) {
    this->data.clear();
    this->data.push_back(meshIn);
}

void MeshComponent::addMesh(const Mesh& meshIn) {
    this->data.push_back(meshIn);
}

void MeshComponent::reset() {
this->data.clear();
}

Mesh MeshComponent::getMesh() {
    return this->data.front();
}
