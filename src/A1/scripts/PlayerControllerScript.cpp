//
// Created by dim on 22/03/2021.
//

#define _USE_MATH_DEFINES

#include "PlayerControllerScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../../core/Game.h"
#include "../CONFIG.h"


void PlayerControllerScript::start() {

}

void PlayerControllerScript::update() {
    Entity* player = this->getParent();
    Vector3 pos = player->getPosition();
    Quaternion rot = player->getRotation();


    float playerSpeed = SHIP_SPEED * Game::dt;
    float forwardXMove = playerSpeed * -sinf(rot.w * (float)M_PI / 180);
    float forwardYMove = playerSpeed * cosf(rot.w * (float)M_PI / 180);


    // Forward
    if(KeyRegistry::isPressed(SHIP_FORWARD_KEY)){
        pos.x += forwardXMove;
        pos.y += forwardYMove;
    }

    // Left/right movement
    if(KeyRegistry::isPressed(SHIP_TURN_LEFT_KEY)){
        rot.w += SHIP_TURN_SPEED;
        rot.z += 1;

    }else if(KeyRegistry::isPressed(SHIP_TURN_RIGHT_KEY)){
        rot.w -= SHIP_TURN_SPEED;
        rot.z += 1;
    }




    player->setPosition(pos);
    player->setRotation(rot);
}
