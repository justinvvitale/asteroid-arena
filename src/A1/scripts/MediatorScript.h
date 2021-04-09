//
// Created by Justin on 3/04/2021.
//

#ifndef I3D_MEDIATORSCRIPT_H
#define I3D_MEDIATORSCRIPT_H

#include "../../core/shared/engine_graphic.h"

#include "../../core/ecs/components/ScriptComponent.h"
#include "../../core/ecs/components/TextComponent.h"
#include "../../core/ecs/components/MeshComponent.h"

class MediatorScript : public ScriptComponent {
private:
    TextComponent* message;
    TextComponent* anyKey;

    // Ensure no keys are pressed before recognising key strokes
    bool registeredEmpty = false;

    int lastState = -1;

protected:
    void start() override;

    void update() override;
};


#endif //I3D_MEDIATORSCRIPT_H
