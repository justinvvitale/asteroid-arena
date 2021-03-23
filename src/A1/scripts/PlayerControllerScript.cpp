//
// Created by dim on 22/03/2021.
//

#define _USE_MATH_DEFINES

#include "PlayerControllerScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../../core/Game.h"
#include "../GAMECONFIG.h"


void PlayerControllerScript::start() {

}

void PlayerControllerScript::update() {
    Entity* player = this->getParent();
    Vector3 pos = player->getPosition();
    Quaternion rot = player->getRotation();



    // Forward
    if (KeyRegistry::isPressed(SHIP_FORWARD_KEY)) {
        if (velocity < 1) {
            velocity += SHIP_ACCELERATION;
        }
    } else if (velocity > 0) {
        // Reset velocity if not moving
        velocity -= SHIP_DECELERATION;

        // Set 0 once respectfully no longer useful
        if (velocity < 0.001) {
            velocity = 0;
        }
    }

    // Move if velocity more than 0
    if (velocity > 0) {
        float shipSpeed = (SHIP_MAX_SPEED * velocity) * Game::dt;
        float forwardXMove = shipSpeed * -sinf(rot.w * (float) M_PI / 180);
        float forwardYMove = shipSpeed * cosf(rot.w * (float) M_PI / 180);

        pos.x += forwardXMove;
        pos.y += forwardYMove;
    }

    // Left/right movement
    if (KeyRegistry::isPressed(SHIP_TURN_LEFT_KEY)) {
        rot.w += SHIP_TURN_SPEED;
        rot.z += 1;

    } else if (KeyRegistry::isPressed(SHIP_TURN_RIGHT_KEY)) {
        rot.w -= SHIP_TURN_SPEED;
        rot.z += 1;
    }

    player->setPosition(pos);
    player->setRotation(rot);
}

void PlayerControllerScript::onCollision(Entity* other) {
}
