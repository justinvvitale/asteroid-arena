//
// Created by Dimme on 8/03/2021.
//

#include "InputRegistry.h"

#if __APPLE__
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif

// Initialize to nothing, should be set by init
std::set<unsigned char>* InputRegistry::keyState = nullptr;
bool InputRegistry::primaryPressed = false;
float InputRegistry::mouseAngleH = 0;
float InputRegistry::mouseAngleV = 0;

Vector2 InputRegistry::centerPoint = Vector2::zero();
void InputRegistry::init() {
    keyState = new std::set<unsigned char>();
    centerPoint.x = glutGet(GLUT_WINDOW_WIDTH)/2;
    centerPoint.y = glutGet(GLUT_WINDOW_HEIGHT)/2;
}

// Call backs

void InputRegistry::keyPress(unsigned char key, int x, int y) {
    keyState->emplace(key);
}

void InputRegistry::keyUp(unsigned char key, int x, int y) {
    keyState->erase(key);
}

// Interface

void InputRegistry::clear() {
    keyState->clear();
}

bool InputRegistry::isPressed(unsigned char key) {
    return keyState->find(key) != keyState->end();
}

std::vector<unsigned char> InputRegistry::getPressed() {
    return std::vector<unsigned char>(keyState->begin(), keyState->end());
}

void InputRegistry::mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON ){
        primaryPressed = state == GLUT_DOWN ? true : false;
    }
}

bool InputRegistry::isPrimaryMousePressed() {
    return primaryPressed;
}

void InputRegistry::mouseMotion(int x, int y) {
    mouseAngleV += (y - centerPoint.y) * 0.03;
    mouseAngleH += (x - centerPoint.x) * 0.03;


    if (x != centerPoint.x || y != centerPoint.y) glutWarpPointer(centerPoint.x, centerPoint.y);
}




