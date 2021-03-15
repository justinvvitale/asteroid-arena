//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_SYSTEM_H
#define I3D_SYSTEM_H

#include <list>
#include "Component.h"

class System {
private:
    ComponentType handleType;

public:
    explicit System(ComponentType handleType){
        this->handleType = handleType;
    };

    virtual void init() {};

    virtual void process(std::list<Component*> items) = 0;

    ComponentType getType(){
        return handleType;
    };
};

#endif //I3D_SYSTEM_H
