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

    float fraction = 20 * Game::dt;
    float turnSpeed = 2.3f * Game::dt;

    Vector3 pos = getEntity()->getPosition();
    Rotation rot = getEntity()->getRotation();

    if (KeyRegistry::isPressed('a')) {
        player->setRotation(this->getEntity()->getRotation() *= player->getRotation().FromEuler(Vector3::up() * -turnSpeed));
    }

    if (KeyRegistry::isPressed('d')) {
        player->setRotation(player->getRotation() *= player->getRotation().FromEuler(Vector3::up() * turnSpeed));
    }

    if (KeyRegistry::isPressed('q')){
        pos.y += 100 *  Game::dt;
    }

    if (KeyRegistry::isPressed('e')){
        pos.y -= 100 *  Game::dt;
    }

    if (Game::state != 1) {
        return;
    }


    // Forward
    if (KeyRegistry::isPressed('w') > 0) {
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
        pos = pos + this->getEntity()->getForwardVector() * (SHIP_MAX_SPEED * velocity) * (Game::dt);
    }

    this->getEntity()->setPosition(pos);

    // Particle for moving
    int elapsed = Game::elapsed;

    // Shooting..
    if (elapsed - lastShoot >= SHIP_SHOOT_COOLDOWN) {
        if (KeyRegistry::isPrimaryMousePressed()) {
            Game::getEngine()->getScene()->addEntity(BulletEntity::getEntity(player->getWorldPosition(),
                                                                             this->getEntity()->getForwardVector() *
                                                                             SHIP_MAX_SPEED * SHIP_SHOOT_VELOCITY));
            lastShoot = elapsed;
        }
    }

    Game::getEngine()->camera->getEntity()->setPosition(this->getEntity()->getPosition().opposite());
    Game::getEngine()->camera->getEntity()->setRotation(this->getEntity()->getRotation());
}
