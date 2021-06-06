//
// Created by Justin on 2/04/2021.
//

#include "TextComponent.h"

#include <utility>

TextComponent::TextComponent() : Component(ComponentType::CText) {}

TextComponent::TextComponent(std::string text, Vector3 pos, float size, TextOrigin origin) : Component(
        ComponentType::CText) {
    this->text = std::move(text);

    this->origin = origin;
    this->offset = pos;
    this->size = size;
}

void TextComponent::setPosition(const Vector3& position) {
    TextComponent::offset = position;
}

const std::string& TextComponent::getText() const {
    return text;
}

void TextComponent::setText(const std::string& text) {
    this->text = text;
}

const Vector3& TextComponent::getOffset() const {
    return offset;
}

float TextComponent::getSize() const {
    return size;
}

TextOrigin TextComponent::getOrigin() const {
    return origin;
}

void TextComponent::setOrigin(TextOrigin origin) {
    TextComponent::origin = origin;
}
