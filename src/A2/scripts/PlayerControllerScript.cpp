//
// Created by dim on 21/04/2021.
//

#include "PlayerControllerScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../../core/Game.h"
#include "../GAMECONFIG.h"
#include "../entities/BulletEntity.h"

void PlayerControllerScript::start() {
    camera = Game::getEngine()->camera;

}

void PlayerControllerScript::update() {
    if (Game::state != 1) {
        return;
    }

    Entity* player = this->getEntity();
    Vector3 pos = player->getPosition();
    Rotation rot = player->getRotation();

   Vector3 cameraLook = camera->getDirectionVector();

    // Particle for moving
    int elapsed = Game::elapsed;

    // Shooting..
    if (elapsed - lastShoot >= SHIP_SHOOT_COOLDOWN) {
        if (KeyRegistry::isPrimaryMousePressed()) {
            Game::getEngine()->getScene()->addEntity(BulletEntity::getEntity(player->getWorldPosition(),
                                                                             cameraLook *
                                                                             SHIP_MAX_SPEED * SHIP_SHOOT_VELOCITY));
            lastShoot = elapsed;
        }
    }

    // Forward
    if (KeyRegistry::isPressed(SHIP_FORWARD_KEY)) {
        if (velocity < 1) {
            velocity += SHIP_ACCELERATION * Game::dt;
        }


        if (elapsed - lastParticleEmit >= SHIP_EXHAUST_DROP_RATE) {
//            emitter->emit(
//                    new Particle(VectorUtil::GetForwardVector(this->getEntity()->getRotation()).opposite() * SHIP_EXHAUST_SPEED, SHIP_EXHAUST_LIFE,
//                                 SHIP_EXHAUST_START_SIZE, SHIP_EXHAUST_END_SIZE,
//                                 MeshHelper::getHexagonMesh((float) SHIP_SIZE / 8, Vector3(1, 0.3, 0))));
            lastParticleEmit = elapsed;
        }

    } else if (velocity > 0) {
        // Reset velocity if not moving
        velocity -= SHIP_DECELERATION * Game::dt;

        // Set 0 once respectfully no longer useful
        if (velocity < 0.001) {
            velocity = 0;
        }
    }


    // Left/right movement
    if (KeyRegistry::isPressed('a')) {
        player->setRotation(Rotation(rot.x, rot.y + 10, rot.z));
    }

    if (KeyRegistry::isPressed('d')) {
        player->setRotation(Rotation(rot.x, rot.y - 10, rot.z));
    }

    // Move if velocity more than 0 (MOVE)
    if (velocity > 0) {
        player->setPosition(pos + cameraLook * (SHIP_MAX_SPEED * velocity) * (Game::dt));
    }

//
//    Vector3 playerPos = getEntity()->getPosition();
//
//    if (KeyRegistry::isPressed('w')) {
//        playerPos.x += cameraLook.x * factor;
//        playerPos.z += cameraLook.z * factor;
//    }
//
//    if (KeyRegistry::isPressed('s')) {
//        playerPos.x -= cameraLook.x * factor;
//        playerPos.z -= cameraLook.z * factor;
//    }
//
//    if (KeyRegistry::isPressed('q')) {
//        playerPos.y +=  factor;
//    }
//
//    if (KeyRegistry::isPressed('e')) {
//        playerPos.y -= factor;
//    }
//
//    getEntity()->setPosition(playerPos);
}
