//
// Created by dim on 22/03/2021.
//
#include "PlayerControllerScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../GAMECONFIG.h"
#include "../entities/BulletEntity.h"
#include "../GameState.h"


void PlayerControllerScript::start() {
    emitter = dynamic_cast<ParticleEmitterComponent*>(this->getEntity()->getComponentOfType(ComponentType::CParticle));

}

void PlayerControllerScript::update() {

    if(Game::state != 1){
        return;
    }

    Entity* player = this->getEntity();
    Vector3 pos = player->getPosition();
    Rotation rot = player->getRotation();

    // Particle for moving
    int elapsed = Game::elapsed;

    // Shooting..
    if(elapsed - lastShoot >= SHIP_SHOOT_COOLDOWN) {
        if (KeyRegistry::isPressed(SHIP_SHOOT_KEY)) {
            Game::getEngine()->getScene()->addEntity(BulletEntity::getEntity(player->getWorldPosition(),
                                                                             VectorUtil::GetForwardVector(rot) *
                                                                             SHIP_MAX_SPEED * SHIP_SHOOT_VELOCITY));
            lastShoot = elapsed;
        }
    }

    // Forward
    if (KeyRegistry::isPressed(SHIP_FORWARD_KEY)) {
        if (velocity < 1) {
            velocity += SHIP_ACCELERATION * Game::dt;
        }


        if(elapsed - lastParticleEmit >= 60) {
            emitter->emit(
                    new Particle(VectorUtil::GetForwardVector(this->getEntity()->getRotation()).opposite() * 200, 150,
                                 2.5, 0.5,
                                 MeshHelper::getHexagonMesh((float) SHIP_SIZE / 8, Vector3(1, 0.3, 0))));
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

    // Left/right movement (ROTATE)
    if (KeyRegistry::isPressed(SHIP_TURN_LEFT_KEY)) {
        rot.angle += SHIP_TURN_SPEED * (Game::dt);
        rot.z += 1;
        player->setRotation(rot);

    } else if (KeyRegistry::isPressed(SHIP_TURN_RIGHT_KEY)) {
        rot.angle -= SHIP_TURN_SPEED * (Game::dt);
        rot.z += 1;
        player->setRotation(rot);
    }

    // Move if velocity more than 0 (MOVE)
    if (velocity > 0) {
        player->setPosition(pos + VectorUtil::GetForwardVector(rot) * (SHIP_MAX_SPEED * velocity) * (Game::dt));
    }

}

void PlayerControllerScript::onCollision(Entity* other) {
    if(other->getTag() == "bullet"){
        return;
    }

    Game::state = GameState::Dead;
}