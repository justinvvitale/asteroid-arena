//
// Created by dim on 2/06/2021.
//

#include "ArenaDestroy.h"
#include "../../core/Game.h"

void ArenaDestroy::start() {
}

void ArenaDestroy::update() {
    if(!isInsideCube(this->getEntity()->getPosition(), ARENA_SIZE)){
        Game::getEngine()->getScene()->removeEntity(this->getEntity());
        Game::queueEntityCleanup(this->getEntity());
    }
}
