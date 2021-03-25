//
// Created by dim on 24/03/2021.
//

#include "AsteroidScript.h"
#include "../../core/Game.h"

AsteroidScript::AsteroidScript(AsteroidWaveScript* mgr, float radius, float speed) {
    this->mgr = mgr;
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

//void AsteroidScript::onCollision(Entity* other) {
//    mgr->despawnAsteroid(other);
//}
