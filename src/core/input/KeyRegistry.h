//
// Created by Dimme on 8/03/2021.
//

#ifndef I3D_KEYREGISTRY_H
#define I3D_KEYREGISTRY_H

#include <iostream>
#include <set>
#include <vector>
#include "../shared/engine_math.h"

class KeyRegistry {
private:
    KeyRegistry() = default;

    static std::set<unsigned char>* keyState;

    static bool primaryPressed;

    static Vector2 centerPoint;
    static Vector2 mouseMove;
    static Vector2 lastMotion;

public:
    static void init();

    static void keyPress(unsigned char key, int x, int y);

    static void keyUp(unsigned char key, int x, int y);

    static void mouse(int button, int state, int x, int y);

    static void mouseMotion(int x, int y);

    static void clear();

    static bool isPressed(unsigned char key);

    static std::vector<unsigned char> getPressed();

    static bool isPrimaryMousePressed();


    static Vector2 getMouseMove();
};


#endif //I3D_KEYREGISTRY_H
