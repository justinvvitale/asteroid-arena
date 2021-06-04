//
// Created by dim on 24/03/2021.
//

#include "ParticleEmitterComponent.h"

ParticleEmitterComponent::ParticleEmitterComponent() : Component(ComponentType::CParticle) {

}

ParticleEmitterComponent::ParticleEmitterComponent(Vector3 offset) : Component(ComponentType::CParticle) {
    this->offset = offset;
}

void ParticleEmitterComponent::emit(Particle* particle) {
    particle->position = getEntity()->getWorldPosition() + getEmitOffset();
    particleBuffer.push_back(particle);
}


std::list<Particle*> ParticleEmitterComponent::takeParticles() {
    std::list<Particle*> particleCpy = particleBuffer;
    particleBuffer.clear();

    return particleCpy;
}

bool ParticleEmitterComponent::hasBufferedParticles() {
    return !particleBuffer.empty();
}

Vector3 ParticleEmitterComponent::getOffset() const {
    return offset;
}

Vector3 ParticleEmitterComponent::getEmitOffset() {
    return offset;
}

