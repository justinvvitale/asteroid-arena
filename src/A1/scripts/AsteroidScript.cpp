//
// Created by dim on 24/03/2021.
//

#include "AsteroidScript.h"
#include "../GAMECONFIG.h"

AsteroidScript::AsteroidScript(AsteroidWaveScript* mgr, float health, float radius, float speed) {
    this->mgr = mgr;
    this->health = health;
    this->radius = radius;
    this->speed = speed;
}

void AsteroidScript::start() {

}

void AsteroidScript::update() {

}

float AsteroidScript::getRadius() const {
    return radius;
}

float AsteroidScript::getSpeed() const {
    return speed;
}

void AsteroidScript::onCollision(Entity* other) {
    if(other->getTag() == "bullet"){
        other->destroy();
        health -= SHIP_BULLET_DAMAGE;

        if(health <= 0){
            mgr->destroyAsteroid(this->getEntity(), true);
        }
    }
}
