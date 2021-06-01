//
// Created by dim on 27/04/2021.
//

#include "TestScript.h"
#include "../../core/Game.h"

void TestScript::start() {
}

void TestScript::update() {
    this->getEntity()->setRotation(this->getEntity()->getRotation() *= this->getEntity()->getRotation().FromEuler(Vector3(0.7,0.2,0.5) * 0.01));
}
