//
// Created by Dimme on 8/03/2021.
//

#include "KeyRegistry.h"

// Initialize to nothing, should be set by init
std::set<unsigned char> *KeyRegistry::keyState = nullptr;


void KeyRegistry::init() {
    keyState = new std::set<unsigned char>();
}

// Call backs

void KeyRegistry::keyPress(unsigned char key, int x, int y) {
    keyState->emplace(key);
}

void KeyRegistry::keyUp(unsigned char key, int x, int y) {
    keyState->erase(key);
}

// Interface

void KeyRegistry::clear() {
    keyState->clear();
}

bool KeyRegistry::isPressed(unsigned char key) {
    return keyState->find(key) != keyState->end();
}

std::vector<unsigned char> KeyRegistry::getPressed() {
    return std::vector<unsigned char>(keyState->begin(), keyState->end());
}




