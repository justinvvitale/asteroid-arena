//
// Created by Dimme on 10/03/2021.
//

#include "MeshComponent.h"
#include "../../Renderer.h"

MeshComponent::MeshComponent() : Component(ComponentType::CMesh) {
}

void MeshComponent::tick() {
    // Load any textures on first tick
    if(isStartTick){
        if(mesh.textureRef == 0 && !mesh.texture.empty()){
            mesh.textureRef = Renderer::loadTexture(mesh.texture);
        }

    isStartTick = false;
    }
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



