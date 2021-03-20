//
// Created by dim on 21/03/2021.
//

#include <iostream>
#include "randmove.h"

void randmove::start() {
    srand (time(NULL));
}

void randmove::update() {
    //std::cout << "hey" << std::endl;
    Entity* test = this->getParent();


    float tesst = rand() % 1000 + 1;

    test->setPosition(Vector3(tesst,tesst,0));
}
