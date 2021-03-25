//
// Created by Dimme on 11/03/2021.
//

#include "ScriptComponent.h"

void ScriptComponent::tick() {
    if (!hasInit) {
        start();
        hasInit = true;
    }

    update();
}

ScriptComponent::ScriptComponent() : Component(ComponentType::CScript) {

}
