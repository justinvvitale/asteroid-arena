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
    switch(this->meshType){
        case Raw:
            for (const Mesh& mesh : data) {
                Renderer::renderMeshData(mesh);
            }
            break;
        case Obj:
            if(objModel != nullptr){
                Renderer::push();
                Renderer::scale(this->scale);
                objModel->draw();
                Renderer::pop();
            }
            break;
        case None:
            break;
    }
}

void MeshComponent::setObjMesh(const std::string& objPath) {
    this->meshType = MeshType::Obj;
    delete objModel;

    objModel = new ObjModel();
    objModel->load(objPath);
}

void MeshComponent::setRawMesh(const Mesh& meshIn) {
    this->meshType = MeshType::Raw;
    this->data.clear();
    this->data.push_back(meshIn);
}

void MeshComponent::addRawMesh(const Mesh& meshIn) {
    this->meshType = MeshType::Raw;
    this->data.push_back(meshIn);
}

void MeshComponent::reset() {
    this->data.clear();
}

Mesh MeshComponent::getRawMesh() {
    return this->data.front();
}

void MeshComponent::setScale(float newScale) {
    this->scale = newScale;
}

MeshComponent::~MeshComponent() {
    delete objModel;
}


