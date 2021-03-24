//
// Created by dim on 22/03/2021.
//
#include "PlayerControllerScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../../core/Game.h"
#include "../GAMECONFIG.h"


void PlayerControllerScript::start() {
    emitter = dynamic_cast<ParticleEmitterComponent*>(this->getParent()->getComponentOfType(ComponentType::CParticle));

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

        emitter->Emit(new Particle(Vector3(0,0,0), 60, MeshHelper::getPointMesh(10)));
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
        float shipSpeed = (SHIP_MAX_SPEED * velocity) * (1 + Game::dt);
        float forwardXMove = shipSpeed * -sinf(rot.w * (float) PI / 180);
        float forwardYMove = shipSpeed * cosf(rot.w * (float) PI / 180);

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
    Game::restart();
}
