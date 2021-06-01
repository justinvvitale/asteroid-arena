//
// Created by dim on 21/04/2021.
//

#include "PlayerControllerScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../../core/Game.h"
#include "../GAMECONFIG.h"
#include "../entities/BulletEntity.h"
#include "../GameState.h"

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
        player->setRotation(this->getEntity()->getRotation() *= player->getRotation().FromEuler(Vector3::up() * turnSpeed));
    }

    if (KeyRegistry::isPressed('d')) {
        player->setRotation(player->getRotation() *= player->getRotation().FromEuler(Vector3::up() * -turnSpeed));
    }

    if (KeyRegistry::isPressed('q')){
        pos.y -= 100 *  Game::dt;
    }

    if (KeyRegistry::isPressed('e')){
        pos.y += 100 *  Game::dt;
    }

    if (Game::state != 1) {
        return;
    }


    // Forward
    if (KeyRegistry::isPressed('w')) {
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

    Vector3 forwardVec = this->getEntity()->getForwardVector();

    // Move if velocity more than 0 (MOVE)
    if (velocity > 0) {
        pos = pos + forwardVec * (SHIP_MAX_SPEED * velocity) * (Game::dt);
    }

    this->getEntity()->setPosition(pos);

    // Particle for moving
    int elapsed = Game::elapsed;

    // Shooting..
    if (elapsed - lastShoot >= SHIP_SHOOT_COOLDOWN) {
        if (KeyRegistry::isPrimaryMousePressed()) {
            Game::getEngine()->getScene()->addEntity(BulletEntity::getEntity(player->getWorldPosition() + forwardVec * 20,
                                                                             forwardVec *
                                                                             SHIP_MAX_SPEED * SHIP_SHOOT_VELOCITY));
            lastShoot = elapsed;
        }
    }


    // What a bloody hack job, atleast it works...
    // I hate rotations :(
    camera->getEntity()->setPosition(VectorUtil::Lerp(camera->getEntity()->getPosition(), this->getEntity()->getPosition().opposite(), Game::dt * 22));
    Vector3 curRot = this->getEntity()->getRotation().ToEuler();
    Vector3 newRot = Vector3(-0.01, -curRot.y, 0);

    camera->rotOffset = Rotation::Rotation::FromEuler(Vector3(0,-59.7,0));
    camera->posOffset = Vector3(0,-2,10);

    Game::getEngine()->camera->getEntity()->setRotation(Rotation::Rotation::FromEuler(newRot));
}

void PlayerControllerScript::onCollision(Entity* other) {

    // Die on asteroid touch
    if(other->getTag() == "asteroid"){
        Game::state = GameState::Dead;
    }
}
