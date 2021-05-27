//
// Created by dim on 23/03/2021.
//

#include "WallScript.h"
#include "../GAMECONFIG.h"
#include "../../core/Game.h"
#include "AsteroidScript.h"

void WallScript::start() {
    this->meshComponent = dynamic_cast<MeshComponent*>(this->getEntity()->getComponentOfType(ComponentType::CMesh));

    this->mesh = Mesh();

    // Setup cords
    float halfSize = ARENA_SIZE / 2;

    // Vertexes
    // Bottom
    Vertex* bottomNearLeft = new Vertex();
    bottomNearLeft->position = Vector3(-halfSize,-halfSize,halfSize);
    Vertex* bottomNearRight = new Vertex();
    bottomNearRight->position = Vector3(halfSize,-halfSize,halfSize);
    Vertex* bottomFarLeft = new Vertex();
    bottomFarLeft->position = Vector3(-halfSize,-halfSize,-halfSize);
    Vertex* bottomFarRight = new Vertex();
    bottomFarRight->position = Vector3(halfSize,-halfSize,-halfSize);

    // Top
    Vertex* topNearLeft = new Vertex();
    topNearLeft->position = Vector3(-halfSize,halfSize,halfSize);
    Vertex* topNearRight = new Vertex();
    topNearRight->position = Vector3(halfSize,halfSize,halfSize);
    Vertex* topFarLeft = new Vertex();
    topFarLeft->position = Vector3(-halfSize,halfSize,-halfSize);
    Vertex* topFarRight = new Vertex();
    topFarRight->position = Vector3(halfSize,halfSize,-halfSize);

    // Add vertices
    mesh.vertices.push_back(bottomNearLeft);
    mesh.vertices.push_back(bottomNearRight);
    mesh.vertices.push_back(bottomFarLeft);
    mesh.vertices.push_back(bottomFarRight);

    mesh.vertices.push_back(topNearLeft);
    mesh.vertices.push_back(topNearRight);
    mesh.vertices.push_back(topFarLeft);
    mesh.vertices.push_back(topFarRight);

    // Faces

    Face bottomFace = Face(FaceType::quad);
    bottomFace.colour = Vector3::zero();
    bottomFace.vertices[0] = bottomNearLeft;
    bottomFace.vertices[1] = bottomNearRight;
    bottomFace.vertices[2] = bottomFarRight;
    bottomFace.vertices[3] = bottomFarLeft;

    Face topFace = Face(FaceType::quad);
    topFace.colour = Vector3::zero();
    topFace.vertices[0] = topNearLeft;
    topFace.vertices[1] = topFarLeft;
    topFace.vertices[2] = topFarRight;
    topFace.vertices[3] = topNearRight;

    Face leftFace = Face(FaceType::quad);
    leftFace.colour = Vector3::zero();
    leftFace.vertices[0] = topNearLeft;
    leftFace.vertices[1] = bottomNearLeft;
    leftFace.vertices[2] = bottomFarLeft;
    leftFace.vertices[3] = topFarLeft;

    Face rightFace = Face(FaceType::quad);
    rightFace.colour = Vector3::zero();
    rightFace.vertices[0] = topNearRight;
    rightFace.vertices[1] = topFarRight;
    rightFace.vertices[2] = bottomFarRight;
    rightFace.vertices[3] = bottomNearRight;

    Face farFace = Face(FaceType::quad);
    farFace.colour = Vector3::zero();
    farFace.vertices[0] = bottomFarLeft;
    farFace.vertices[1] = bottomFarRight;
    farFace.vertices[2] = topFarRight;
    farFace.vertices[3] = topFarLeft;

    Face nearFace = Face(FaceType::quad);
    nearFace.colour = Vector3::zero();
    nearFace.vertices[0] = bottomNearLeft;
    nearFace.vertices[1] = topNearLeft;
    nearFace.vertices[2] = topNearRight;
    nearFace.vertices[3] = bottomNearRight;

    // Add faces
    mesh.faces.push_back(topFace);
    topFaceIndex = 0;
    mesh.faces.push_back(bottomFace);
    bottomFaceIndex = 1;
    mesh.faces.push_back(leftFace);
    leftFaceIndex = 2;
    mesh.faces.push_back(rightFace);
    rightFaceIndex = 3;
    mesh.faces.push_back(farFace);
    farFaceIndex = 4;
    mesh.faces.push_back(nearFace);
    nearFaceIndex = 5;

    refreshMeshData();
}

void WallScript::update() {
    int prevWarns = topWarn + bottomWarn + leftWarn + rightWarn + nearWarn + farWarn;


    if(Game::paused){
        topWarn = false;
        bottomWarn = false;
        leftWarn = false;
        rightWarn = false;

    }else {
        Vector3 playerPos = Game::getEntity("player")->getPosition();
        float halfSize = ARENA_SIZE / 2;

        topWarn = halfSize - playerPos.y <= ARENA_WARN_DIST;
    }
    int currentWarns = topWarn + bottomWarn + leftWarn + rightWarn + nearWarn + farWarn;

    // Only redraw (probably costly) if something has changed
    if (prevWarns != currentWarns) {
        refreshMeshData();
    }
}


void WallScript::refreshMeshData() {
    if(topWarn){
        mesh.faces[topFaceIndex].colour = Vector3(0.5,0.5,1);
    }else{
        mesh.faces[topFaceIndex].colour = Vector3::zero();
    }

    this->meshComponent->setMesh(mesh);
}

void WallScript::onCollision(Entity* other) {
//    if (other->getTag() == "bullet") {
//        other->destroy();
//    }
//
//    if (other->getTag() == "asteroid") {
//        AsteroidScript* ast = dynamic_cast<AsteroidScript*>(other->getComponentOfType(ComponentType::CScript));
//
//        if (ast->isPrimed()) {
//            RigidbodyComponent* rigid = dynamic_cast<RigidbodyComponent*>(other->getComponentOfType(
//                    ComponentType::CRigidbody));
//            Vector3 vel = Vector3(rigid->getVelocity().opposite());
//            rigid->clearVelocity();
//
//            Vector3 asteroidPosition = other->getOffset();
//
//            float minDistBottomTop = min(
//                    VectorUtil::DistanceFromLine(topLeftVert, topRightVert, asteroidPosition),
//                    VectorUtil::DistanceFromLine(bottomLeftVert, bottomRightVert, asteroidPosition)
//            );
//            float minDistLeftRight = min(
//                    VectorUtil::DistanceFromLine(topLeftVert, bottomLeftVert, asteroidPosition),
//                    VectorUtil::DistanceFromLine(topRightVert, bottomRightVert, asteroidPosition)
//            );
//
//            if (minDistLeftRight <= minDistBottomTop) {
//                // Hit a left/right wall
//                rigid->addForce(vel.x, -vel.y, 0);
//            } else {
//                // Hit a top/bottom wall
//                rigid->addForce(-vel.x, vel.y, 0);
//            }
//
//            ast->resetPrimed();
//        }
//    }
}
