//
// Created by Justin on 1/04/2021.
//

#include "ScoreScript.h"
#include "../../core/Game.h"
#include "MediatorScript.h"
#include "../GameState.h"

void ScoreScript::start() {
    std::list<Component*> textComps = getEntity()->getComponentsOfType(ComponentType::CText);

    auto iter = textComps.begin();
    uiRefKill = (TextComponent*) *iter++;
    uiRefTime = (TextComponent*) *iter++;
    uiRefWave = (TextComponent*) *iter;
}


void ScoreScript::update() {
    if (Game::state != GameState::Initial) {
        uiRefWave->setText(
                (isCD && Game::state == GameState::Playing) ? "INTERMISSION" : ("Wave: " + std::to_string(wave)));
    }

    if (Game::state != 1) return;

    int seconds = Game::elapsedSeconds;

    if (seconds != lastSecondCheck) {
        lastSecondCheck = seconds;

        elapsedSeconds++;

        if (elapsedSeconds >= 60) {
            elapsedSeconds = 0;
            elapsedMinutes++;
        }

        uiRefTime->setText(std::to_string(elapsedMinutes) + "m " + std::to_string(elapsedSeconds) + "s");
    }

    if (dirtyScore) {
        uiRefKill->setText("Score: " + std::to_string(score));
        dirtyScore = false;
    }

}

void ScoreScript::addScore(int amount) {
    this->score += amount;
    dirtyScore = true;
}

void ScoreScript::clearScore() {
    this->score = 0;
    dirtyScore = true;
}

int ScoreScript::getScore() const {
    return score;
}



