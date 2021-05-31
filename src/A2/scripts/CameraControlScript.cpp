//
// Created by dim on 31/05/2021.
//

#include "CameraControlScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../../core/Game.h"
#include "../GAMECONFIG.h"

void CameraControlScript::start() {
    cam = dynamic_cast<CameraComponent*>(this->getEntity()->getComponentOfType(CCamera));
    player = Game::getEntity("player");
}

void CameraControlScript::update() {
    float fraction = 20 * Game::dt;
    float turnSpeed = 2.3f * Game::dt;

    Vector3 pos = getEntity()->getPosition();
    Rotation rot = getEntity()->getRotation();

    if (KeyRegistry::isPressed('a')) {
        rot.y += turnSpeed;
    }

    if (KeyRegistry::isPressed('d')) {
        rot.y -= turnSpeed;
    }

    if (Game::state != 1) {
        return;
    }

    VectorUtil::Print(rot.direction());



    // Forward
    if (KeyRegistry::isPressed(SHIP_FORWARD_KEY)) {
        if (velocity < 1) {
            velocity += SHIP_ACCELERATION * Game::dt;
        }

    } else if (velocity > 0) {
        // Reset velocity if not moving
        velocity -= SHIP_DECELERATION * Game::dt;

        // Set 0 once respectfully no longer useful
        if (velocity < 0.001) {
            velocity = 0;
        }
    }

    // Move if velocity more than 0 (MOVE)
    if (velocity > 0) {
        this->getEntity()->setPosition(pos + rot.direction() * (SHIP_MAX_SPEED * velocity) * (Game::dt));
    }

    this->getEntity()->setRotation(rot);


//    // Move player to camera
//    Vector3 playerPos = player->getPosition();
//    Rotation playerRot = player->getRotation();
//    //this->player->setPosition();
//    //this->player->setRotation(Rotation(0,0,0));
}
