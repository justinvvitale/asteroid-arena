//
// Created by Dimme on 10/03/2021.
//

#include "Engine.h"
#include "Scene.h"
#include "ecs/components/MeshComponent.h"
#include "ecs/components/ScriptComponent.h"

void Engine::test() {

    Scene scene = Scene();

    Entity *entity = new Entity();
    Component *component = new MeshComponent();
    Component *component1 = new ScriptComponent();


    entity->addComponent(component);
    entity->addComponent(component1);
    scene.addEntity(entity);

    auto test = scene.findComponentsOfType<MeshComponent>();

}