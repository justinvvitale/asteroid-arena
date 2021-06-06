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
    Vector3 colour;
    std::string texture;

    Particle(Vector3 vel, float lifeSpanMs, float startScale, float endScale, const std::string& texture,
             Vector3 colour = DEFAULT_COLOUR) {
        this->velocity = vel;
        this->life = lifeSpanMs;
        this->scale = startScale;

        this->lifeSpan = lifeSpanMs;
        this->startScale = startScale;
        this->endScale = endScale;

        this->texture = texture;
        this->colour = colour;
    }
} Particle;


class ParticleEmitterComponent : public Component {
private:
    std::list<Particle*> particleBuffer = std::list<Particle*>();

    // Offset based off forward vector
    Vector3 offset;

public:
    ParticleEmitterComponent();

    explicit ParticleEmitterComponent(Vector3 offset);

    void emit(Particle* particle);

    Vector3 getEmitOffset();

    bool hasBufferedParticles();

    std::list<Particle*> takeParticles();

    Vector3 getOffset() const;
};


#endif //I3D_PARTICLEEMITTERCOMPONENT_H
