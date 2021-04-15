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
    static std::list<Particle*> particles;

    long int lastLifeDecrement = -1;
public:
    ParticleSystem();

    void init() override;

    void process(std::list<Component*> items) override;

    // Manual emit
    static void emit(Particle* particle, Vector3 position);

    void render();

    // Cleanup particles and delete
    void cleanup() override;
};


#endif //I3D_PARTICLESYSTEM_H
