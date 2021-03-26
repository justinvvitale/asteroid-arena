//
// Created by dim on 24/03/2021.
//

#ifndef I3D_PARTICLEEMITTERCOMPONENT_H
#define I3D_PARTICLEEMITTERCOMPONENT_H


#include "../Component.h"

#include <utility>
#include "MeshComponent.h"
#include "../../Game.h"

typedef struct Particle {
    // State
    Vector3 position;
    Vector3 velocity;
    float scale;
    float life;

    // Description
    float lifeSpan;
    float startScale;
    float endScale;
    Mesh mesh;

    Particle(Vector3 vel, float lifeSpanMs, float startScale, float endScale, Mesh meshIn) {
        this->velocity = vel;
        this->life = lifeSpanMs;
        this->scale = startScale;

        this->lifeSpan = lifeSpanMs;
        this->startScale = startScale;
        this->endScale = endScale;

        this->mesh = std::move(meshIn);
    }
} Particle;


class ParticleEmitterComponent : public Component {
private:
    std::list<Particle*> particleBuffer = std::list<Particle*>();

    // Offset based off forward vector
    float offset = 0;

public:
    ParticleEmitterComponent();

    ParticleEmitterComponent(float offset);

    void Emit(Particle* particle);

    Vector3 getEmitOffset();

    bool hasBufferedParticles();

    std::list<Particle*> TakeParticles();

    float getOffset() const;
};


#endif //I3D_PARTICLEEMITTERCOMPONENT_H
