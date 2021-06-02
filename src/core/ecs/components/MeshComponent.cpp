//
// Created by Dimme on 10/03/2021.
//

#include "MeshComponent.h"

#include <utility>
#include "../../Renderer.h"

MeshComponent::MeshComponent() : Component(ComponentType::CMesh) {

}

MeshComponent::MeshComponent(CustomRenderMesh customRenderMesh) : Component(ComponentType::CMesh) {
    this->isCustomRender = true;
    this->customRenderMesh = std::move(customRenderMesh);
}

void MeshComponent::tick() {
}

void MeshComponent::render() {
    if(!isCustomRender){
        Renderer::scale(this->scale);
            Renderer::renderMesh(mesh);
        Renderer::scale(-scale);

    }else{
        // Render if textures (If any)
        if(!customRenderMesh.texture.empty()){
            Renderer::TextureStart(customRenderMesh.texture);
            Renderer::renderCustom(customRenderMesh.customRender, customRenderMesh.param1, customRenderMesh.param2, customRenderMesh.param3);
            Renderer::TextureEnd();
        }else{
            Renderer::renderCustom(customRenderMesh.customRender, customRenderMesh.param1, customRenderMesh.param2, customRenderMesh.param3);
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



