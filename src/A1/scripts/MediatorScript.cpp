//
// Created by Justin on 3/04/2021.
//

#include "MediatorScript.h"
#include "../../core/input/KeyRegistry.h"
#include "../global.h"


void MediatorScript::start() {
    blackout = Mesh();
    blackout.mode = GL_QUADS;
    blackout.colour = Vector3(0,0,0);
    blackout.data = {
            MeshData(1000, -1000, 0),
            MeshData(1000, 1000, 0),
            MeshData(-1000, 1000, 0),
            MeshData(-1000, -1000, 0)
    };

    message = new TextComponent("Welcome to star");
    anyKey = new TextComponent("Press any key to continue");

    mesh = dynamic_cast<MeshComponent*>(getEntity()->getComponentOfType(CMesh));
 }

void MediatorScript::update() {
    if(STATE_GLOBAL != lastState){
        lastState = STATE_GLOBAL;

        switch (lastState) {
            case STATE_BEGIN: // Initial
            mesh->setMesh(blackout);
            getEntity()->addComponent(message);
            getEntity()->addComponent(anyKey);

                break;
            case STATE_PLAY: // Playing (Hide everything)
                mesh->reset();
                getEntity()->removeComponent(message);
                getEntity()->removeComponent(anyKey);
                break;
            case STATE_DEAD: // Game over, man

                break;
        }
    }

    // Await input
    if(lastState != STATE_PLAY){
        if(!KeyRegistry::getPressed().empty()){
            STATE_GLOBAL = STATE_PLAY;
        }
    }
}


