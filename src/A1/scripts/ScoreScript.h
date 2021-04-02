//
// Created by Justin on 1/04/2021.
//

#ifndef I3D_SCORESCRIPT_H
#define I3D_SCORESCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"
#include "../../core/ecs/components/TextComponent.h"

class ScoreScript : public ScriptComponent {
private:
    int score;

    TextComponent* uiRefKill;
    TextComponent* uiRefTime;

    int lastSecondCheck = -1;

    int elapsedSeconds = 0;
    int elapsedMinutes = 0;
    bool dirtyScore = true;

protected:
    void update() override;

    void start() override;

public:
    void addScore(int amount);
    void clearScore();

    int getScore() const;
};


#endif //I3D_SCORESCRIPT_H
