//
// Created by dim on 21/03/2021.
//

#ifndef I3D_SCRIPTPROCESSORSYSTEM_H
#define I3D_SCRIPTPROCESSORSYSTEM_H


#include "../System.h"

class ScriptProcessorSystem : public System {

    void init() override;
    void process(std::list<Component*> items) override;

public:
    ScriptProcessorSystem();
};


#endif //I3D_SCRIPTPROCESSORSYSTEM_H
