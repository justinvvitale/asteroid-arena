//
// Created by Justin on 1/04/2021.
//

#ifndef I3D_SCORESCRIPT_H
#define I3D_SCORESCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"

class ScoreScript : public ScriptComponent {
private:
    int score;

protected:
    void update() override;

    void start() override;

public:
    void addScore(int amount);
    void clearScore();

    int getScore() const;
};


#endif //I3D_SCORESCRIPT_H
