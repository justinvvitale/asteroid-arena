//
// Created by Justin on 1/04/2021.
//

#include "ScoreScript.h"
#include "../../core/Game.h"

void ScoreScript::start() {
    std::list<Component*> textComps = getEntity()->getComponentsOfType(ComponentType::CText);

    uiRefKill = (TextComponent*)textComps.front();
    uiRefTime = (TextComponent*)textComps.back();
}


void ScoreScript::update() {

    int seconds = Game::elapsedSeconds;

    if(seconds != lastSecondCheck){
        lastSecondCheck = seconds;

        elapsedSeconds++;

        if(elapsedSeconds >= 60){
            elapsedSeconds = 0;
            elapsedMinutes++;
        }

        uiRefTime->setText(std::to_string(elapsedMinutes) + "m " + std::to_string(elapsedSeconds) + "s");
    }

    if(dirtyScore){
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



