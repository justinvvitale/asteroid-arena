//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_SYSTEM_H
#define I3D_SYSTEM_H

#include <list>

class System {
private:
    int priority = 0;
public:
    System(){};

    virtual void init() {};

    virtual void process(std::list<C *> items) = 0;

    // 1000 is IMPORTANT | -1000 UNIMPORTANT
    int getPriority(){
            return priority;
    };
};


#endif //I3D_SYSTEM_H
