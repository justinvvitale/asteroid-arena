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
        entity->addComponent((Component*) new TextComponent("", Vector3(0.5, -1.5, 0), 0.5, TextOrigin::topLeft));
        entity->addComponent((Component*) new TextComponent("", Vector3(-8, -1.5, 0), 0.5, TextOrigin::topRight));
        entity->addComponent((Component*) new TextComponent("", Vector3(0.5, 0.5, 0), 0.5, TextOrigin::bottomLeft));


        return entity;
    }

};


#endif //I3D_SCOREMANAGERENTITY_H
