//
// Created by dim on 21/04/2021.
//

#include "PlayerControllerScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../../core/Game.h"

void PlayerControllerScript::start() {
}

void PlayerControllerScript::update() {
    float factor = 80 * Game::dt;

    CameraComponent* camera = Game::getEngine()->camera;
    Vector3 cameraLook = Vector3::zero();
    if(camera != nullptr) {
        cameraLook = camera->getDirectionVector();
    }

    // Boost
    if(KeyRegistry::isPressed(32)){
        factor *= 3;
    }

    Vector3 playerPos = getEntity()->getPosition();

    if (KeyRegistry::isPressed('w')) {
        playerPos.x += cameraLook.x * factor;
        playerPos.z += cameraLook.z * factor;
    }

    if (KeyRegistry::isPressed('s')) {
        playerPos.x -= cameraLook.x * factor;
        playerPos.z -= cameraLook.z * factor;
    }

    if (KeyRegistry::isPressed('q')) {
        playerPos.y +=  factor;
    }

    if (KeyRegistry::isPressed('e')) {
        playerPos.y -= factor;
    }

    getEntity()->setPosition(playerPos);
}
