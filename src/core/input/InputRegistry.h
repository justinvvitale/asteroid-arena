//
// Created by Dimme on 8/03/2021.
//

#ifndef I3D_INPUTREGISTRY_H
#define I3D_INPUTREGISTRY_H

#include <iostream>
#include <set>
#include <vector>
#include "../shared/engine_math.h"

class InputRegistry {
private:
    InputRegistry() = default;

    static std::set<unsigned char>* keyState;

    static bool primaryPressed;

    static Vector2 centerPoint;
    static Vector2 lastMotion;

public:
    static float mouseAngleH;
    static float mouseAngleV;

    static void init();

    static void keyPress(unsigned char key, int x, int y);

    static void keyUp(unsigned char key, int x, int y);

    static void mouse(int button, int state, int x, int y);

    static void mouseMotion(int x, int y);

    static void clear();

    static bool isPressed(unsigned char key);

    static std::vector<unsigned char> getPressed();

    static bool isPrimaryMousePressed();
};


#endif //I3D_INPUTREGISTRY_H
