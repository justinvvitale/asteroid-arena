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

        emitter->Emit(new Particle(getForwardVector(rot).opposite() * 10, 20, MeshHelper::getPointMesh(10)));
    } else if (velocity > 0) {
        // Reset velocity if not moving
        velocity -= SHIP_DECELERATION;

        // Set 0 once respectfully no longer useful
        if (velocity < 0.001) {
            velocity = 0;
        }
    }

    // Left/right movement (ROTATE)
    if (KeyRegistry::isPressed(SHIP_TURN_LEFT_KEY)) {
        rot.w += SHIP_TURN_SPEED;
        rot.z += 1;
        player->setRotation(rot);

    } else if (KeyRegistry::isPressed(SHIP_TURN_RIGHT_KEY)) {
        rot.w -= SHIP_TURN_SPEED;
        rot.z += 1;
        player->setRotation(rot);
    }

    // Move if velocity more than 0 (MOVE)
    if (velocity > 0) {
        player->setPosition(pos + getForwardVector(rot) * (SHIP_MAX_SPEED * velocity) * (1 + Game::dt));
    }

}

void PlayerControllerScript::onCollision(Entity* other) {
    Game::restart();
}

Vector3 PlayerControllerScript::getForwardVector(Quaternion rotation) {
    return {(-sinf(rotation.w * (float) PI / 180)),(cosf(rotation.w * (float) PI / 180)), 0};
}
