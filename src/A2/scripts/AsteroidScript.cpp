//
// Created by dim on 24/03/2021.
//

#include "AsteroidScript.h"

#include <utility>
#include "../GAMECONFIG.h"
#include "../../core/ecs/components/RigidbodyComponent.h"
#include "../../core/audio/AudioPlayer.h"
#include "../../core/ecs/components/ColliderComponent.h"
#include "../entities/AsteroidEntity.h"

AsteroidScript::AsteroidScript(AsteroidWaveScript* mgr, float health, float radius, float speed, std::string texture,
                               bool canSplit) {
    this->mgr = mgr;
    this->health = health;
    this->radius = radius;
    this->speed = speed;
    this->texture = std::move(texture);

    this->canSplit = canSplit;
}

void AsteroidScript::start() {
    lastSecondCheck = Game::elapsedSeconds;
    MeshComponent* meshRenderer = new MeshComponent();
    meshRenderer->setMesh(AsteroidEntity::getModel(radius, getRandomNumber(ASTEROID_STACK_MIN, ASTEROID_STACK_MAX),
                                                   getRandomNumber(ASTEROID_SECTOR_MIN, ASTEROID_SECTOR_MAX), texture));

    this->getEntity()->addComponent(new ColliderComponent(sphere, radius));

    this->getEntity()->addComponent(meshRenderer);
}

void AsteroidScript::update() {
    int elapsedSeconds = Game::elapsedSeconds;
    if (lastSecondCheck != Game::elapsedSeconds) {
        this->alive++;
        lastSecondCheck = elapsedSeconds;
    }

    // Prime once hasn't collided and been alive for atleast 3 seconds
    if (!primed &&
        (!canSplit || isInsideCube(this->getEntity()->getPosition(), ARENA_SIZE, this->radius) && alive >= 2)) {
        this->primed = true;
    }

    if (isPrimed() && !isInsideCube(this->getEntity()->getPosition(), ARENA_SIZE, this->radius)) {
        RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(this->getEntity()->getComponentOfType(
                ComponentType::CRigidbody));
        Vector3 vel = Vector3(rigid->getVelocity());
        rigid->clearVelocity();

        // TODO more accurate bounce (maybe)
        rigid->addForce(vel.opposite());

        resetPrimed();
    }
}


float AsteroidScript::getRadius() const {
    return radius;
}

float AsteroidScript::getSpeed() const {
    return speed;
}

void AsteroidScript::onCollision(Entity* other) {
    if (other->getTag() == "bullet") {
        other->destroy();
        health -= SHIP_BULLET_DAMAGE;

        if (health <= 0) {
            AudioPlayer::playOnce("explode");

            // Create two new asteroids
            if (canSplit) {
                mgr->splitAsteroid(this->getEntity(), true);
            } else {
                mgr->destroyAsteroid(this->getEntity(), true);
            }
        }
    }

    if (ASTEROID_COLLISION) {
        if (primed && other->getTag() == "asteroid") {
            RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(this->getEntity()->getComponentOfType(
                    ComponentType::CRigidbody));

            Vector3 impactPoint = VectorUtil::MidPoint(this->getEntity()->getWorldPosition(),
                                                       other->getWorldPosition());
            Vector3 force = VectorUtil::Normalize(this->getEntity()->getWorldPosition() - impactPoint) * this->speed;

            rigid->clearVelocity();
            rigid->addForce(force);
        }
    }
}

bool AsteroidScript::isPrimed() const {
    return primed;
}

void AsteroidScript::resetPrimed() {
    this->primed = false;
}

const std::string& AsteroidScript::getTexture() const {
    return texture;
}
