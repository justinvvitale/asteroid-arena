//
// Created by dim on 21/04/2021.
//

#include "PlayerControllerScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../../core/Game.h"

void PlayerControllerScript::start() {
    updateCamera();
}

void PlayerControllerScript::update() {
    float change = + 300 * Game::dt;

    bool didMove = false;

    if(KeyRegistry::isPressed('w')){
        cameraPos.z -= change;
        didMove = true;
    }

    if(KeyRegistry::isPressed('s')){
        cameraPos.z += change;
        didMove = true;
    }

    if(KeyRegistry::isPressed('q')){
        cameraPos.y -= change;
        didMove = true;
    }

    if(KeyRegistry::isPressed('e')){
        cameraPos.y += change;
        didMove = true;
    }

    if(KeyRegistry::isPressed('a')){
        cameraPos.x -= change;
        didMove = true;
    }

    if(KeyRegistry::isPressed('d')){
        cameraPos.x += change;
        didMove = true;
    }

    if(didMove){
        updateCamera();
    }
}

void PlayerControllerScript::updateCamera() const {
    gluLookAt(
            cameraPos.x, cameraPos.y, cameraPos.z,  // eye location
            0.0,  0.0,   0.0,
            0.0,  1.0,   0.0    // up vector
    );
}
