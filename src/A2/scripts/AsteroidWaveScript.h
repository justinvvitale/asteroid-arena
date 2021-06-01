//
// Created by dim on 24/03/2021.
//

#ifndef I3D_ASTEROIDWAVESCRIPT_H
#define I3D_ASTEROIDWAVESCRIPT_H


#include <set>
#include "ScoreScript.h"

class AsteroidWaveScript : public ScriptComponent {
private:
    std::set<Entity*> asteroids = std::set<Entity*>();
    ScoreScript* scoreScript;

    int asteroidSpawnAmount = 0;

    int cdStartTime = -1;
    int lastClearTime = -1;

    Vector3 getPositionOutOfArena(float payloadSize) const;

    void spawnAsteroid();

    void spawnAsteroid(float health, Vector3 position, float speed, float radius, float rotation, Vector3 force,
                       bool canSplit);

    Entity* shipRef;

protected:
    void update() override;

    void start() override;

public:
    void splitAsteroid(Entity* asteroid, bool scored = false);

    void destroyAsteroid(Entity* asteroid, bool scored);
};


#endif //I3D_ASTEROIDWAVESCRIPT_H
