//
// Created by dim on 24/03/2021.
//

#ifndef I3D_PARTICLEEMITTERCOMPONENT_H
#define I3D_PARTICLEEMITTERCOMPONENT_H


#include "../Component.h"
#include "MeshComponent.h"

typedef struct Particle{
    Vector3 position;
    Vector3 velocity;
    float life;

    Mesh mesh;

    Particle(Vector3 vel, float lifeSpan, Mesh meshIn){
        this->velocity = vel;
        this->life = lifeSpan;
        this->mesh = meshIn;
    }
} Particle;


class ParticleEmitterComponent : public Component {
private:
    Vector3 emitPosition;
    std::list<Particle*> particleBuffer = std::list<Particle*>();

public:
    ParticleEmitterComponent(Vector3 emitPosition = Vector3::zero());

    void Emit(Particle* particle);

    Vector3 getEmitOffset();

    bool hasBufferedParticles();
    std::list<Particle*> TakeParticles();
};


#endif //I3D_PARTICLEEMITTERCOMPONENT_H
