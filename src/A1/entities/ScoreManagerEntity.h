//
// Created by Justin on 1/04/2021.
//

#ifndef I3D_SCOREMANAGERENTITY_H
#define I3D_SCOREMANAGERENTITY_H

#include "../scripts/ScoreScript.h"
#include "../../core/ecs/components/TextComponent.h"

class ScoreManagerEntity {
private:
    static Mesh getModel() {
        Mesh mesh;
        mesh.mode = GL_LINE_LOOP;
        mesh.data = {
                MeshData(-100, -100, 0),
                MeshData(100, -100, 0),
                MeshData(100, 100, 0),
                MeshData(-100, 100, 0)
        };

        return mesh;
    }

public:
    static Entity* getEntity() {
        auto* entity = new Entity("score");

        entity->addComponent((Component*) new ScoreScript());
        entity->addComponent((Component*) new TextComponent("", Vector3(-980, 880, 0), 0.5));
        entity->addComponent((Component*) new TextComponent("", Vector3(680, 880, 0), 0.5));
        entity->addComponent((Component*) new TextComponent("", Vector3(-980, -980, 0), 0.5));


        return entity;
    }

};


#endif //I3D_SCOREMANAGERENTITY_H
