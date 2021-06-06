//
// Created by dim on 23/03/2021.
//

#include "ArenaScript.h"
#include "../GAMECONFIG.h"
#include "../../core/Game.h"
#include "../GameState.h"

void ArenaScript::start() {
    this->meshComponent = dynamic_cast<MeshComponent*>(this->getEntity()->getComponentOfType(ComponentType::CMesh));
    customRender = CustomRenderMesh(CustomRender::Arena, "", ARENA_SIZE, ARENA_SPACING);

    meshComponent->setMesh(customRender);
}

void ArenaScript::update() {
    if (!Game::paused) {
        Vector3 playerPos = Game::getEntity("player")->getPosition();

        // I don't like this system, should be re-factored and decoupled from game engine.
        customRender.param1 = playerPos.x;
        customRender.param2 = playerPos.y;
        customRender.param3 = playerPos.z;

        meshComponent->setMesh(customRender);

        // Kill check (Player)
        if (!isInsideCube(playerPos, ARENA_SIZE)) {
            Game::state = GameState::Dead;
        }
    }
}
