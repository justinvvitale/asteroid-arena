//
// Created by dim on 24/03/2021.
//

#ifndef I3D_PARTICLESYSTEM_H
#define I3D_PARTICLESYSTEM_H


#include "../System.h"
#include "../components/ParticleEmitterComponent.h"
#include <list>

class ParticleSystem : public System {
private:
    std::list<Particle*> particles = std::list<Particle*>();
public:
    ParticleSystem();

    void init() override;

    void process(std::list<Component*> items) override;
    void render();

    // Cleanup particles and delete
    void cleanup() override;
};


#endif //I3D_PARTICLESYSTEM_H
