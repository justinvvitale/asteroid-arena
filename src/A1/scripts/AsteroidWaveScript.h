//
// Created by dim on 24/03/2021.
//

#ifndef I3D_ASTEROIDWAVESCRIPT_H
#define I3D_ASTEROIDWAVESCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"

class AsteroidWaveScript : public ScriptComponent {
private:
    std::list<Entity*> asteroids = std::list<Entity*>();

    float launchRadius;

    Vector3 getPositionOutOfArena(float payloadSize) const;
    void spawnAsteroid();

    Entity* playerRef;

protected:
    void update() override;

    void start() override;

};


#endif //I3D_ASTEROIDWAVESCRIPT_H
