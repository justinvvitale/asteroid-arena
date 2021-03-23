//
// Created by Dimme on 11/03/2021.
//

#ifndef I3D_MESHRENDERERSYSTEM_H
#define I3D_MESHRENDERERSYSTEM_H


#include "../components/MeshComponent.h"
#include "../System.h"

class MeshRendererSystem : public System {
public:
    MeshRendererSystem();
    void process(std::list<Component*> items) override;

private:
   Entity* getRootEntity(Entity* entity);
   void renderEntity(Entity* entity);
   void debugRender(Entity* entity);
};


#endif //I3D_MESHRENDERERSYSTEM_H
