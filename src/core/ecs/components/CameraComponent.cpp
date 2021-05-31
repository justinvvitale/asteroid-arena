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
    // Set camera position behind player
    Vector3 globalPosition = getEntity()->getPosition();

    Renderer::moveCamera(globalPosition, this->getEntity()->getRotation().direction());
}

CameraComponent::~CameraComponent() {
    CameraComponent* camera = Game::getEngine()->camera;

    if(camera == this){
        camera = nullptr;
    }
}

Vector3 CameraComponent::getDirectionVector() {
    return this->getEntity()->getRotation().direction();
}

