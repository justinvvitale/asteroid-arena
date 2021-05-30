//
// Created by Dimme on 10/03/2021.
//

#include "MeshComponent.h"
#include "../../Renderer.h"

MeshComponent::MeshComponent(CustomRender customRender) : Component(ComponentType::CMesh) {
    this->customRender = customRender;
}

void MeshComponent::tick() {
}

void MeshComponent::render() {
    if(customRender == CustomRender::None){
        Renderer::renderMesh(mesh);
    }else{
        Renderer::renderCustom(customRender);
    }
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

Mesh MeshComponent::getMesh() {
    return mesh;
}



