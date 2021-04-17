//
// Created by dim on 24/03/2021.
//

#include "AsteroidScript.h"
#include "../GAMECONFIG.h"
#include "../../core/ecs/components/RigidbodyComponent.h"

AsteroidScript::AsteroidScript(AsteroidWaveScript* mgr, float health, float radius, float speed, bool canSplit) {
    this->mgr = mgr;
    this->health = health;
    this->radius = radius;
    this->speed = speed;

    this->canSplit = canSplit;
}

void AsteroidScript::start() {

}

void AsteroidScript::update() {

    if (!didCollideArenaOuter) {
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
            other->getRotation();
            RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(this->getEntity()->getComponentOfType(
                    ComponentType::CRigidbody));
            Vector3 vel = rigid->getVelocity();
            rigid->clearVelocity();
            rigid->addForce(vel.opposite());
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
