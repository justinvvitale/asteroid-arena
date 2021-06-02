//
// Created by Dimme on 10/03/2021.
//

#include "MeshComponent.h"
#include "../../Renderer.h"

MeshComponent::MeshComponent(CustomRender customRender, std::string customRendererTexture) : Component(ComponentType::CMesh) {
    this->customRender = customRender;
    this->customRendererTexture = customRendererTexture;
}

void MeshComponent::tick() {
}

void MeshComponent::render() {
    if(customRender == CustomRender::None){
        Renderer::scale(this->scale);
            Renderer::renderMesh(mesh);
        Renderer::scale(-scale);

    }else{
        // Render if textures (If any)
        if(!customRendererTexture.empty()){
            Renderer::TextureStart(customRendererTexture);
            Renderer::renderCustom(customRender, this->scale);
            Renderer::TextureEnd();
        }else{
            Renderer::renderCustom(customRender, this->scale);
        }
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



