//
// Created by dim on 24/04/2021.
//

#include "CameraComponent.h"
#include "../../input/KeyRegistry.h"
#include "../../Game.h"
#include "../../Renderer.h"
#include "../../shared/engine_graphic.h"

CameraComponent::CameraComponent() : Component(ComponentType::CCamera) {
    Game::getEngine()->camera = this;
}

void CameraComponent::tick() {
}

void CameraComponent::render() {
    // The camera entity is special, it's the centre of the damn map
    Vector3 globalPosition = getEntity()->getWorldPosition() + Vector3(0,0,-50);
    Rotation rotation = getEntity()->getRotation();

    Renderer::rotate(rotation);
    Renderer::move(globalPosition);
w

}

CameraComponent::~CameraComponent() {
    CameraComponent* camera = Game::getEngine()->camera;

    if(camera == this){
        camera = nullptr;
    }
}

Vector3 CameraComponent::getDirectionVector() {
    return this->getEntity()->getForwardVector();
}

