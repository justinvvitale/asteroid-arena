//
// Created by dim on 2/06/2021.
//

#include "DelayDestroy.h"
#include "../../core/Game.h"

void DelayDestroy::start() {
    startMs = Game::elapsed;

}

void DelayDestroy::update() {
    if(Game::elapsed - startMs >= fuse){
        Game::getEngine()->getScene()->removeEntity(this->getEntity());
        Game::queueEntityCleanup(this->getEntity());
    }

}

DelayDestroy::DelayDestroy(float fuseMs) {
    fuse = fuseMs;
}
