//
// Created by dim on 24/03/2021.
//

#include "AsteroidScript.h"
#include "../GAMECONFIG.h"
#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../../core/Game.h"

AsteroidScript::AsteroidScript(AsteroidWaveScript* mgr, float health, float radius, float speed, bool canSplit) {
    this->mgr = mgr;
    this->health = health;
    this->radius = radius;
    this->speed = speed;

    this->canSplit = canSplit;
}

void AsteroidScript::start() {
    lastSecondCheck = Game::elapsedSeconds;
}

void AsteroidScript::update() {
    int elapsedSeconds = Game::elapsedSeconds;
    if(lastSecondCheck != Game::elapsedSeconds){
        this->alive++;
        lastSecondCheck = elapsedSeconds;
    }

    // Prime once hasn't collided and been alive for atleast 3 seconds
    if (!canSplit || !didCollideArenaOuter && alive >= 2) {
        this->primed = true;
    }

    didCollideArenaOuter = false;
}


float AsteroidScript::getRadius() const {
    return radius;
}

float AsteroidScript::getSpeed() const {
    return speed;
}

void AsteroidScript::onCollision(Entity* other) {
    if (other->getTag() == "bullet") {
        other->destroy();
        health -= SHIP_BULLET_DAMAGE;

        if (health <= 0) {
            // Create two new asteroids
            if (canSplit) {
                mgr->splitAsteroid(this->getEntity(), true);
            } else {
                mgr->destroyAsteroid(this->getEntity(), true);

            }
        }
    }

    if (other->getTag() == "arena") {
        didCollideArenaOuter = true;
    }


    if(ASTEROID_COLLISION) {
        if (primed && other->getTag() == "asteroid") {
            RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(this->getEntity()->getComponentOfType(
                    ComponentType::CRigidbody));

            Vector3 impactPoint = VectorUtil::MidPoint(this->getEntity()->getWorldPosition(), other->getWorldPosition());
            Vector3 force = VectorUtil::Normalize(this->getEntity()->getWorldPosition() - impactPoint) * this->speed;

            rigid->clearVelocity();
            rigid->addForce(force);
        }
    }
}

bool AsteroidScript::isPrimed() const {
    return primed;
}

void AsteroidScript::resetPrimed() {
    this->primed = false;
    didCollideArenaOuter = true;
}
