//
// Created by Justin on 2/04/2021.
//

#include "TextRendererSystem.h"
#include "../components/TextComponent.h"
#include "../../Renderer.h"

TextRendererSystem::TextRendererSystem() : System(ComponentType::CText) {}

void TextRendererSystem::process(std::list<Component*> items) {
    for (Component* component : items) {
        TextComponent* textComponent = (TextComponent*) component;

        Renderer::renderText(textComponent->getOrigin(), textComponent->getOffset(), textComponent->getText(), textComponent->getSize());
    }
}
