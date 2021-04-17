//
// Created by dim on 24/03/2021.
//

#include "ParticleSystem.h"
#include "../../Game.h"
#include "../../Renderer.h"

std::list<Particle*> ParticleSystem::particles = std::list<Particle*>();

ParticleSystem::ParticleSystem() : System(ComponentType::CParticle) {
}

void ParticleSystem::init() {

}

void ParticleSystem::process(std::list<Component*> items) {
    for (Component* component : items) {
        ParticleEmitterComponent* emitter = dynamic_cast<ParticleEmitterComponent*>(component);
        if (emitter->hasBufferedParticles()) {
            auto bufferedParticles = emitter->takeParticles();
            particles.insert(particles.end(), bufferedParticles.begin(), bufferedParticles.end());
        }
    }

    long int elapsedMs = Game::elapsed;
    int elapsedDiffMS = elapsedMs - lastLifeDecrement;
    bool decrementLife = elapsedDiffMS >= 1;

    // Churn existing particles (Move, tick life, remove finished)
    auto particleIter = particles.begin();
    while (particleIter != particles.end()) {
        Particle* particle = *particleIter;

        if (decrementLife) {
            particle->life -= elapsedDiffMS;

            // If end of life, destroy. Increment iter for next loop
            if (particle->life <= 0) {
                delete particle;
                particles.erase(particleIter++);
                continue;
            }
        }

        // Apply velocity
        particle->position = (particle->position + (particle->velocity * Game::dt));

        float percentLifeSpan = particle->life / particle->lifeSpan;
        particle->scale = Lerp(particle->endScale, particle->startScale, percentLifeSpan);

        ++particleIter;
    }

    lastLifeDecrement = elapsedMs; // Move our ms counter
}

void ParticleSystem::render() {
    for (Particle* particle : particles) {
        Renderer::renderParticle(particle);
    }
}

void ParticleSystem::cleanup() {
    auto particleIter = particles.begin();
    while (particleIter != particles.end()) {
        Particle* particle = *particleIter;
        delete particle;
        particles.erase(particleIter++);
    }
}

void ParticleSystem::emit(Particle* particle, Vector3 position) {
    particle->position = position;
    particles.push_back(particle);
}
