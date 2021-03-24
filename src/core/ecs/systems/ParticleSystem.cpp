//
// Created by dim on 24/03/2021.
//

#include "ParticleSystem.h"
#include "../../Game.h"
#include "../../Renderer.h"

ParticleSystem::ParticleSystem() : System(ComponentType::CParticle) {

}

void ParticleSystem::init() {

}

void ParticleSystem::process(std::list<Component*> items) {
    for(Component* component : items){
        ParticleEmitterComponent* emitter = dynamic_cast<ParticleEmitterComponent*>(component);
        if(emitter->hasBufferedParticles()){
            auto bufferedParticles = emitter->TakeParticles();
            particles.insert(particles.end(), bufferedParticles.begin(), bufferedParticles.end());
        }
    }

    // Churn existing particles (Move, tick life, remove finished)
    auto particleIter = particles.begin();
    while (particleIter != particles.end()){
        Particle* particle = *particleIter;
        particle->life--;

        // If end of life, destroy. Increment iter for next loop
        if(particle->life <= 0){
            delete particle;
            particles.erase(particleIter++);
            continue;
        }else{
            ++particleIter;
        }

        // Apply velocity
        particle->position = (particle->position + (particle->velocity *  (1 + Game::dt)));
    }
}

void ParticleSystem::render() {
    for(Particle* particle : particles){
        Renderer::renderParticle(particle);
    }
}

void ParticleSystem::cleanup() {
    auto particleIter = particles.begin();
    while (particleIter != particles.end()){
        Particle* particle = *particleIter;
        delete particle;
        particles.erase(particleIter++);
    }
}
