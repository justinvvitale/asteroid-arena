//
// Created by Justin on 2/04/2021.
//

#include "TextRendererSystem.h"
#include "../components/TextComponent.h"
#include "../../Renderer.h"

TextRendererSystem::TextRendererSystem() : System(ComponentType::CText) {}

void TextRendererSystem::process(std::list<Component*> items) {
    for (Component* component : items) {
        TextComponent* textComponent = (TextComponent*)component;

        Renderer::push();
        Renderer::move(textComponent->getPosition());
        Renderer::renderText(textComponent->getText(), textComponent->getSize());
        Renderer::pop();
    }
}
