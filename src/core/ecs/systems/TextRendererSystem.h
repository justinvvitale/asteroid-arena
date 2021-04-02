//
// Created by Justin on 2/04/2021.
//

#ifndef I3D_TEXTRENDERERSYSTEM_H
#define I3D_TEXTRENDERERSYSTEM_H


#include "../System.h"

class TextRendererSystem : public System {

public:
    TextRendererSystem();

    void process(std::list<Component*> items) override;
};


#endif //I3D_TEXTRENDERERSYSTEM_H
