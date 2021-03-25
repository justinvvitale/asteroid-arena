//
// Created by dim on 24/03/2021.
//

#include "ParticleEmitterComponent.h"

ParticleEmitterComponent::ParticleEmitterComponent() : Component(ComponentType::CParticle) {

}

ParticleEmitterComponent::ParticleEmitterComponent(float offset) : Component(ComponentType::CParticle) {
    this->offset = offset;
}

void ParticleEmitterComponent::Emit(Particle* particle) {
    particle->position = getEntity()->getWorldPosition() + getEmitOffset();
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

float ParticleEmitterComponent::getOffset() const {
    return offset;
}

Vector3 ParticleEmitterComponent::getEmitOffset() {
    Vector3 offsetVec = Vector3::zero();

    if (offset != 0) {
        offsetVec = (VectorUtil::GetForwardVector(this->getEntity()->getRotation()) * offset);
    }

    return offsetVec;
}

