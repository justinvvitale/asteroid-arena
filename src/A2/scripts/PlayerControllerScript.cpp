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
}
