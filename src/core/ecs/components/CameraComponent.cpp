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

    if (KeyRegistry::isPressed('a')) {
        camRot -= turnSpeed;
        lookDirection.x = sin(camRot);
        lookDirection.z = -cos(camRot);
    }

    if (KeyRegistry::isPressed('d')) {
        camRot += turnSpeed;
        lookDirection.x = sin(camRot);
        lookDirection.z = -cos(camRot);
    }
}

void CameraComponent::render() {
    Vector3 globalPosition = getEntity()->getPosition() + cameraOffset;

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
