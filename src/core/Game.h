//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_GAME_H
#define I3D_GAME_H

#include <cstdlib>
#include <cstdio>
#include "Engine.h"
#include "shared/engine_graphic.h"
#include <iostream>
#include <queue>
#include <set>

class Game {
private:
    static float lastIdleTime;
    static Engine* engine;

    // Kinda greasy using a function pointer but works well
    typedef Scene* (* defaultScenePointer)();

    static defaultScenePointer getDefaultScene;
    static bool restartRequested;

    static void performEntityCleanup();

    static std::set<Entity*> toDelete;
public:
    // Key variables (Global)

    // Time difference since last tick (Used for smooth animations)
    static float dt;

    // State variable which is determined/used by implementation
    static int state;

    static long int elapsed; // MS
    static long int elapsedSeconds; // S

    // Current tick
    static long int tick;

    static void start(int argc, char** argv, const std::string& name, Scene* (* getDefaultScene)());

    static void restart();

    static void stop();

    static Engine* getEngine();

    static Entity* getEntity(const std::string& tag);

    static void queueEntityCleanup(Entity* item);

    // GLUT callbacks
    static void init();

    static void reshape(int w, int h);

    static void display();

    static void idle();
};


#endif //I3D_GAME_H
