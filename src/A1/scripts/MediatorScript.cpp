//
// Created by Justin on 3/04/2021.
//

#include "MediatorScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../GameState.h"
#include "../../core/Game.h"
#include "../../core/ecs/systems/MeshRendererSystem.h"
#include "../../core/Renderer.h"

void MediatorScript::start() {
    message = new TextComponent("X");
    anyKey = new TextComponent("Press any key to continue", Vector3(-500, -200, 0), 0.6);
}

void MediatorScript::update() {
    int curState = Game::state;
    if (curState != lastState) {
        lastState = curState;

        switch (curState) {
            case GameState::Initial: // Initial
                MeshRendererSystem::setEnabled(false);
                message->setText("Welcome to Space Wars");
                message->setPosition(Vector3(-800, 0, 0));

                getEntity()->addComponent(message);
                getEntity()->addComponent(anyKey);
                break;
            case GameState::Playing: // Playing (Hide everything)
                MeshRendererSystem::setEnabled(true);
                getEntity()->removeComponent(message);
                getEntity()->removeComponent(anyKey);
                Renderer::drawParticles = true;
                break;
            case GameState::Dead: // Game over, man
                MeshRendererSystem::setEnabled(false);
                Renderer::drawParticles = false;

                message->setText("You Died");
                message->setPosition(Vector3(-270, 0, 0));

                getEntity()->addComponent(message);
                getEntity()->addComponent(anyKey);
                break;
        }

        Game::getEngine()->flagDirty();
        registeredEmpty = false;
    }

    // Await input
    if (lastState != GameState::Playing) {
        if (KeyRegistry::getPressed().empty()) {
            registeredEmpty = true;
        } else if (registeredEmpty && !KeyRegistry::getPressed().empty()) {
            // Restart from death
            if (Game::state == GameState::Dead) {
                Game::restart();
            }

            Game::state = GameState::Playing;
        }
    }
}


