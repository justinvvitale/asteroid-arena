//
// Created by Justin on 1/04/2021.
//

#include "ScoreScript.h"

void ScoreScript::start() {

}


void ScoreScript::update() {

}

void ScoreScript::addScore(int amount) {
    this->score += amount;
}

void ScoreScript::clearScore() {
    this->score = 0;
}

int ScoreScript::getScore() const {
    return score;
}



