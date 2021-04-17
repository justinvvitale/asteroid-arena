//
// Created by dim on 23/03/2021.
//

#include "WallScript.h"
#include "../GAMECONFIG.h"
#include "../../core/ENGINECONFIG.h"
#include "../../core/Game.h"
#include "../../core/ecs/components/RigidbodyComponent.h"
#include "AsteroidScript.h"

void WallScript::start() {
    this->meshComponent = dynamic_cast<MeshComponent*>(this->getEntity()->getComponentOfType(ComponentType::CMesh));

    // Setup cords
    float halfWidth = ARENA_WIDTH / 2;
    float halfHeight = ARENA_HEIGHT / 2;

    topLeftVert = Vector3(-halfWidth, halfHeight, 0);
    topRightVert = Vector3(halfWidth, halfHeight, 0);
    bottomLeftVert = Vector3(-halfWidth, -halfHeight, 0);
    bottomRightVert = Vector3(halfWidth, -halfHeight, 0);

    refreshMeshData();
}

void WallScript::update() {
    Vector3 playerPos = Game::getEntity("player")->getPosition();

    int prevWarns = topWarn + bottomWarn + leftWarn + rightWarn;

    topWarn = VectorUtil::DistanceFromLine(topLeftVert, topRightVert, playerPos) <= ARENA_WARN_DIST;
    bottomWarn = VectorUtil::DistanceFromLine(bottomLeftVert, bottomRightVert, playerPos) <= ARENA_WARN_DIST;
    leftWarn = VectorUtil::DistanceFromLine(topLeftVert, bottomLeftVert, playerPos) <= ARENA_WARN_DIST;
    rightWarn = VectorUtil::DistanceFromLine(topRightVert, bottomRightVert, playerPos) <= ARENA_WARN_DIST;

    int currentWarns = topWarn + bottomWarn + leftWarn + rightWarn;

    // Only redraw (probably costly) if something has changed
    if (prevWarns != currentWarns) {
        refreshMeshData();
    }
}

void WallScript::refreshMeshData() {
    Mesh arenaMesh;
    arenaMesh.mode = GL_LINE_STRIP;
    arenaMesh.data = {
            MeshData(MeshDataType::colour, bottomWarn ? ARENA_WARN_COLOUR : ARENA_COLOUR),
            MeshData(bottomLeftVert), // Bottom left
            MeshData(bottomRightVert), // Bottom right
            MeshData(MeshDataType::colour, rightWarn ? ARENA_WARN_COLOUR : ARENA_COLOUR),
            MeshData(topRightVert), // Top right
            MeshData(MeshDataType::colour, topWarn ? ARENA_WARN_COLOUR : ARENA_COLOUR),
            MeshData(topLeftVert), // Top left
            MeshData(MeshDataType::colour, leftWarn ? ARENA_WARN_COLOUR : ARENA_COLOUR),

            MeshData(bottomLeftVert), // Complete loop

            MeshData(MeshDataType::colour, DEFAULT_COLOUR)
    };

    this->meshComponent->setMesh(arenaMesh);
}

void WallScript::onCollision(Entity* other) {
    if (other->getTag() == "bullet") {
        other->destroy();
    }

    if (other->getTag() == "asteroid") {
        AsteroidScript* ast = dynamic_cast<AsteroidScript*>(other->getComponentOfType(ComponentType::CScript));

        if (ast->isPrimed()) {
            RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(other->getComponentOfType(
                    ComponentType::CRigidbody));
            Vector3 vel = Vector3(rigid->getVelocity().opposite());
            rigid->clearVelocity();

            Vector3 asteroidPosition = other->getPosition();

            float minDistBottomTop = std::min(
                    VectorUtil::DistanceFromLine(topLeftVert, topRightVert, asteroidPosition),
                    VectorUtil::DistanceFromLine(bottomLeftVert, bottomRightVert, asteroidPosition)
            );
            float minDistLeftRight = std::min(
                    VectorUtil::DistanceFromLine(topLeftVert, bottomLeftVert, asteroidPosition),
                    VectorUtil::DistanceFromLine(topRightVert, bottomRightVert, asteroidPosition)
            );

            if (minDistLeftRight <= minDistBottomTop) {
                // Hit a left/right wall
                rigid->addForce(vel.x, -vel.y, 0);
            } else {
                // Hit a top/bottom wall
                rigid->addForce(-vel.x, vel.y, 0);
            }

            ast->resetPrimed();
        }
    }
}
