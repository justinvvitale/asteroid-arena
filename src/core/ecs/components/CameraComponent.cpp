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
    float fraction = 20 * Game::dt;
    float turnSpeed = 2.3f * Game::dt;

    // Boost
    if(KeyRegistry::isPressed(32)){
        fraction *= 3;
    }

}

void CameraComponent::render() {
    // Set camera position behind player
    Vector3 globalPosition = getEntity()->getPosition() + cameraOffset;
    globalPosition = Vector3(-globalPosition.y, globalPosition.x, globalPosition.z);

    Renderer::moveCamera(globalPosition, lookDirection);
}

CameraComponent::~CameraComponent() {
    CameraComponent* camera = Game::getEngine()->camera;

    if(camera == this){
        camera = nullptr;
    }
}

Vector3 CameraComponent::getDirectionVector() {
    return lookDirection;
}

const Vector3& CameraComponent::getCameraOffset() const {
    return cameraOffset;
}

void CameraComponent::setCameraOffset(const Vector3& offset) {
    CameraComponent::cameraOffset = offset;
}
