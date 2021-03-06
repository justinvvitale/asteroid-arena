//
// Created by Justin on 3/04/2021.
//

#include "MediatorScript.h"
#include "../../core/input/InputRegistry.h"
#include "../GameState.h"
#include "../../core/ecs/systems/MeshRendererSystem.h"
#include "../../core/audio/AudioPlayer.h"
#include "../../core/ecs/systems/ParticleSystem.h"

void MediatorScript::start() {
    message = new TextComponent("X");
    anyKey = new TextComponent("Press any key to continue...", Vector3(-12, -3, 0), 0.6);
}

void MediatorScript::update() {
    int curState = Game::state;
    if (curState != lastState) {
        lastState = curState;

        switch (curState) {
            case GameState::Initial: // Initial
                MeshRendererSystem::setEnabled(false);
                message->setText("Welcome to Asteroid Arena 3D");
                message->setPosition(Vector3(-24.5, 5, 0));

                AudioPlayer::playOnce("intro");

                getEntity()->addComponent(message);
                getEntity()->addComponent(anyKey);
                break;
            case GameState::Playing: // Playable (Hide everything)
                MeshRendererSystem::setEnabled(true);
                getEntity()->removeComponent(message);
                getEntity()->removeComponent(anyKey);
                Game::paused = false;
                break;
            case GameState::Dead: // Game over, man
                Game::paused = true;

                // Particle Explosion
                for (int i = 0; i < 100; i++) {
                    Vector3 vel = Vector3(
                            (float) getRandomNumber(-200, 200),
                            (float) getRandomNumber(-200, 200),
                            (float) getRandomNumber(-200, 200));

                    ParticleSystem::emit(new Particle(vel, (float) 2000 +
                                                           (float) getRandomNumber(-1000,
                                                                                   1000), 20, 8, "fireball"),
                                         Game::getEntity("player")->getPosition());
                }

                message->setText("Game Over");
                message->setPosition(Vector3(-7, 0, 0));

                // Strip player of stuff which can mess up visuals but still allow it to exist (for particles)
                Entity* player = Game::getEntity("player");
                player->removeComponent(player->getComponentOfType(ComponentType::CCollider));
                player->removeComponent(player->getComponentOfType(ComponentType::CMesh));

                // Audio :)
                AudioPlayer::playOnce("gameover");

                getEntity()->addComponent(message);
                getEntity()->addComponent(anyKey);
                break;
        }

        Game::getEngine()->flagDirty();
        registeredEmpty = false;
    }

    // Await input
    if (lastState != GameState::Playing) {
        if (InputRegistry::getPressed().empty()) {
            registeredEmpty = true;
        } else if (registeredEmpty && !InputRegistry::getPressed().empty()) {
            // Restart from death
            if (Game::state == GameState::Dead) {
                Game::restart();
            }

            Game::state = GameState::Playing;
        }
    }
}


