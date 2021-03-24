//
// Created by dim on 24/03/2021.
//

#include "ParticleEmitterComponent.h"

ParticleEmitterComponent::ParticleEmitterComponent(Vector3 emitPosition) : Component(ComponentType::CParticle) {
    this->emitPosition = emitPosition;
}

void ParticleEmitterComponent::Emit(Particle* particle) {
    particle->position = getParent()->getWorldPosition() + getEmitOffset();
    particleBuffer.push_back(particle);
}


std::list<Particle*> ParticleEmitterComponent::TakeParticles() {
    std::list<Particle*> particleCpy = particleBuffer;
    particleBuffer.clear();

    return particleCpy;
}

bool ParticleEmitterComponent::hasBufferedParticles() {
    return !particleBuffer.empty();
}

Vector3 ParticleEmitterComponent::getEmitOffset() {
    return emitPosition;
}

