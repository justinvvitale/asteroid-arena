//
// Created by dim on 27/04/2021.
//

#include "TestScript.h"
#include "../../core/Game.h"

void TestScript::start() {
}

void TestScript::update() {
    Rotation curRot = this->getEntity()->getRotation();
    this->getEntity()->setRotation(Rotation(curRot.x, curRot.y + 20 * Game::dt, curRot.z));
}
