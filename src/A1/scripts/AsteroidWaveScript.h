//
// Created by dim on 24/03/2021.
//

#ifndef I3D_ASTEROIDWAVESCRIPT_H
#define I3D_ASTEROIDWAVESCRIPT_H


#include <set>
#include "../../core/ecs/components/ScriptComponent.h"

class AsteroidWaveScript : public ScriptComponent {
private:
    std::set<Entity*> asteroids = std::set<Entity*>();

    float launchRadius;

    int lastSpawnTime = -1;
    int lastClearTime = -1;

    Vector3 getPositionOutOfArena(float payloadSize) const;

    void spawnAsteroid();

    Entity* playerRef;

protected:
    void update() override;
    void start() override;

public:
    void despawnAsteroid(Entity* asteroid);
};


#endif //I3D_ASTEROIDWAVESCRIPT_H
