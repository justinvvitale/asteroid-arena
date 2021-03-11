//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_MESHRENDERERSYSTEM_H
#define I3D_MESHRENDERERSYSTEM_H


#include "../components/MeshComponent.h"
#include "../System.h"

class MeshRendererSystem : public System<MeshComponent> {
public:
    void process(std::list<MeshComponent *> items) override;
};


#endif //I3D_MESHRENDERERSYSTEM_H
