//
// Created by dim on 23/03/2021.
//

#include "WallScript.h"
#include "../GAMECONFIG.h"
#include "../../core/Game.h"
#include "AsteroidScript.h"
#include "../../core/ecs/systems/ParticleSystem.h"
#include "../GameState.h"

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
        float halfArena = ARENA_SIZE / 2;

        float distTop = halfArena - playerPos.y;
        float distBottom = halfArena + playerPos.y;
        float distNear =  halfArena - playerPos.z;
        float distFar = halfArena + playerPos.z;
        float distLeft = halfArena + playerPos.x;
        float distRight = halfArena - playerPos.x;

        topWarn = distTop <= ARENA_WARN_DIST;
        bottomWarn = distBottom <= ARENA_WARN_DIST;
        nearWarn = distNear <= ARENA_WARN_DIST;
        farWarn = distFar <= ARENA_WARN_DIST;
        leftWarn = distLeft <= ARENA_WARN_DIST;
        rightWarn = distRight <= ARENA_WARN_DIST;

        // Kill check (Player)
        if(!isInsideCube(playerPos, ARENA_SIZE)){
//            for(int i = 0; i < 100; i++){
//                Vector3 vel = Vector3(
//                        (float) getRandomNumber(-200, 200),
//                        (float) getRandomNumber(-200, 200), 0);
//
//                ParticleSystem::emit(new Particle(vel, (float)2000 +
//                                                       (float)getRandomNumber(-1000,
//                                                                              1000), 2.5, 0.5,
//                                                  MeshHelper::getHexagonMesh((float) SHIP_SIZE / 8, Vector3(1, 0.3, 0))), this->getEntity()->getPosition());
//            }

            Game::state = GameState::Dead;
        }
    }
    int currentWarns = topWarn + bottomWarn + leftWarn + rightWarn + nearWarn + farWarn;

    // Only redraw (probably costly) if something has changed
    if (prevWarns != currentWarns) {
        refreshMeshData();
    }
}


void WallScript::refreshMeshData() {
    Vector3 warnColour = Vector3(0.7, 0,0);
    Vector3 colour = Vector3(0.5, 0.5,0.5);
    if(topWarn){
        mesh.faces[topFaceIndex].colour = Vector3(warnColour);
    }else{
        mesh.faces[topFaceIndex].colour = colour;
    }

    if(bottomWarn){
        mesh.faces[bottomFaceIndex].colour = Vector3(warnColour);
    }else{
        mesh.faces[bottomFaceIndex].colour = colour;
    }

    if(nearWarn){
        mesh.faces[nearFaceIndex].colour = Vector3(warnColour);
    }else{
        mesh.faces[nearFaceIndex].colour = colour;
    }

    if(farWarn){
        mesh.faces[farFaceIndex].colour = Vector3(warnColour);
    }else{
        mesh.faces[farFaceIndex].colour = colour;
    }

    if(leftWarn){
        mesh.faces[leftFaceIndex].colour = Vector3(warnColour);
    }else{
        mesh.faces[leftFaceIndex].colour = colour;
    }

    if(rightWarn){
        mesh.faces[rightFaceIndex].colour = Vector3(warnColour);
    }else{
        mesh.faces[rightFaceIndex].colour = colour;
    }

    this->meshComponent->setMesh(mesh);
}
