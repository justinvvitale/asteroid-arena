//
// Created by dim on 21/04/2021.
//

#include "PlayerControllerScript.h"
#include "../../core/input/InputRegistry.h"
#include "../GAMECONFIG.h"
#include "../entities/BulletEntity.h"
#include "../GameState.h"
#include "../../core/audio/AudioPlayer.h"

void PlayerControllerScript::start() {
    camera = Game::getEngine()->camera;

    auto emitters = getEntity()->getComponentsOfType(CParticle);
}

void PlayerControllerScript::update() {
    if (Game::state != 1) {
        return;
    }


    Vector3 pos = getEntity()->getPosition();
    Rotation rot = getEntity()->getRotation();

    // Clamp values
    // Not needed anymore but good reference
    // InputRegistry::mouseAngleV = Clamp(InputRegistry::mouseAngleV, -SHIP_VERTICAL_VIEW_CLAMP, SHIP_VERTICAL_VIEW_CLAMP);
    float inverter = (rot * Vector3::up()).y;

    Vector3 eulerMods = Vector3::zero();
    eulerMods.y = InputRegistry::mouseAngleH * SHIP_HORIZONTAL_SENSITIVITY;
    eulerMods.x = InputRegistry::mouseAngleV * SHIP_VERTICAL_SENSITIVITY;

    // Always keep the ship up-right TODO kinda annoying
    eulerMods.y = inverter < 0 ? eulerMods.y : -eulerMods.y;

    rot = Rotation::FromEuler(eulerMods);

    if (InputRegistry::isPressed(SHIP_MOVE_UP)){
        pos.y -= 100 *  Game::dt;
    }

    if (InputRegistry::isPressed(SHIP_MOVE_DOWN)){
        pos.y += 100 *  Game::dt;
    }

    if (Game::state != 1) {
        return;
    }

    // Particle for moving
    int elapsed = Game::elapsed;

    // Forward
    if (InputRegistry::isPressed(SHIP_FORWARD_KEY)) {
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
    this->getEntity()->setRotation(rot);

    // Shooting..
    if (elapsed - lastShoot >= SHIP_SHOOT_COOLDOWN) {
        if (InputRegistry::isPrimaryMousePressed()) {
            AudioPlayer::playOnce("shoot");
            Game::getEngine()->getScene()->addEntity(BulletEntity::getEntity(pos + forwardVec * 10,
                                                                             forwardVec *
                                                                             SHIP_MAX_SPEED * SHIP_SHOOT_VELOCITY));
            lastShoot = elapsed;
        }
    }

    float horizontalAngleOffset = 0;

    //Provide a mechanism for the player to look to the Left, Right and Behind the
    //spaceship. This could simply consist of switching the camera to a side or rear view
    //while an appropriate key is pressed down. The ship should not be rendered while the
    //camera is displaying one of these camera views.
    if(InputRegistry::isPressed(SHIP_VIEW_LEFT)){
        horizontalAngleOffset -= 90;
    }else if(InputRegistry::isPressed(SHIP_VIEW_RIGHT)){
        horizontalAngleOffset += 90;
    }else if(InputRegistry::isPressed(SHIP_VIEW_BEHIND)){
        horizontalAngleOffset -= 180;
    }


    // What a bloody hack job, atleast it works...
    // I hate rotations :(
    // Update: Improved it lol
    camera->rotOffset = Rotation::Rotation::FromEuler(Vector3(0,(180 + horizontalAngleOffset) * DEG_TO_RAD,0));
    camera->posOffset = Vector3(0,-2,8);

    camera->getEntity()->setRotation(Rotation::RotateTowards(camera->getEntity()->getRotation(), rot.Inverse(), CAMERA_ROTATION_DAMP * Game::dt));
    camera->getEntity()->setPosition(VectorUtil::Lerp(camera->getEntity()->getPosition(), pos.opposite(),  CAMERA_POSITION_DAMP * Game::dt));
}

void PlayerControllerScript::onCollision(Entity* other) {

    // Die on asteroid touch
    if(other->getTag() == "asteroid"){
        Game::state = GameState::Dead;
    }
}
