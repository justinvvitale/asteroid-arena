//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_ENGINE_H
#define I3D_ENGINE_H

#include "ecs/System.h"

class Engine {
private:
    Engine() = default;

public:
    static Engine &getInstance() {
        static Engine instance;
        return instance;
    }

    Engine(Engine const &) = delete;

    void operator=(Engine const &) = delete;

    void test();
};


#endif //I3D_ENGINE_H
