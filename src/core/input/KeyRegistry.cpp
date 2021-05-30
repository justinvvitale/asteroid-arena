//
// Created by Dimme on 8/03/2021.
//

#include "KeyRegistry.h"

#if __APPLE__
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif

// Initialize to nothing, should be set by init
std::set<unsigned char>* KeyRegistry::keyState = nullptr;
bool KeyRegistry::primaryPressed = false;

Vector2 KeyRegistry::centerPoint = Vector2::zero();
Vector2 KeyRegistry::lastMotion = Vector2::zero();
Vector2 KeyRegistry::mouseMove = Vector2::zero();

void KeyRegistry::init() {
    keyState = new std::set<unsigned char>();
    centerPoint.x = glutGet(GLUT_WINDOW_WIDTH)/2;
    centerPoint.y = glutGet(GLUT_WINDOW_HEIGHT)/2;


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

void KeyRegistry::mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON ){
        primaryPressed = state == GLUT_DOWN ? true : false;
    }
}

bool KeyRegistry::isPrimaryMousePressed() {
    return primaryPressed;
}

void KeyRegistry::mouseMotion(int x, int y) {
    Vector2 curMotion = Vector2((float)x, (float)y);
    mouseMove = mouseMove + (lastMotion - curMotion);
    lastMotion = curMotion;

    if (x != centerPoint.x || y != centerPoint.y) glutWarpPointer(centerPoint.x, centerPoint.y);
}

Vector2 KeyRegistry::getMouseMove() {
    Vector2 returnVec = Vector2(mouseMove.x, mouseMove.y);
    mouseMove = Vector2::zero();
    return returnVec;
}




