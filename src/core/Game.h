//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_GAME_H
#define I3D_GAME_H

#include <cstdlib>
#include <cstdio>
#include "input/KeyRegistry.h"
#include "Engine.h"
#include <iostream>

class Game {
private:
    static float lastIdleTime;
    static Engine* engine;

public:
    // Key variables (Global)

    // Time difference since last tick (Used for smooth animations)
    static float dt;

    // Current tick
    static long int tick;


    static void start(int argc, char **argv, const std::string& name, Engine* gEngine);

    static Engine* getEngine();

    // GLUT callbacks
    static void init();

    static void reshape(int w, int h);

    static void display();

    static void idle();
};


#endif //I3D_GAME_H
