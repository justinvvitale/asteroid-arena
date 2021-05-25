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
    Renderer::renderMesh(mesh);
}

void MeshComponent::setMesh(const Mesh& meshIn) {
    this->mesh = meshIn;
}


void MeshComponent::reset() {
    this->mesh = Mesh();
}


void MeshComponent::setScale(float newScale) {
    this->scale = newScale;
}



