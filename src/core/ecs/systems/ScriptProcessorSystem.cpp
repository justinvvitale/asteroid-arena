//
// Created by dim on 21/03/2021.
//

#include "ScriptProcessorSystem.h"
#include "../components/ScriptComponent.h"

void ScriptProcessorSystem::init() {
    System::init();
}

void ScriptProcessorSystem::process(std::list<Component*> items) {
    for(Component* component : items){
        ScriptComponent* script = dynamic_cast<ScriptComponent*>(component);

        script->tick();
    }

}

ScriptProcessorSystem::ScriptProcessorSystem() : System(ComponentType::CScript){

}
