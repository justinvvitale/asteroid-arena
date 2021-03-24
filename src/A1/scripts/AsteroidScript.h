//
// Created by dim on 24/03/2021.
//

#ifndef I3D_ASTEROIDSCRIPT_H
#define I3D_ASTEROIDSCRIPT_H


#include "../../core/ecs/components/ScriptComponent.h"

class AsteroidScript : public ScriptComponent {
private:
    float radius;
    float speed;
public:
    float getRadius() const;

    float getSpeed() const;

protected:
    void start() override;

    void update() override;

public:
    AsteroidScript(float radius, float speed);


};


#endif //I3D_ASTEROIDSCRIPT_H
