//
// Created by dim on 21/03/2021.
//

#ifndef I3D_ARENAENTITY_H
#define I3D_ARENAENTITY_H


class ArenaEntity {
private:
    static struct Mesh getModel(){
        struct Mesh arenaMesh;
        arenaMesh.mode = GL_LINE_LOOP;
        arenaMesh.data = {
                MeshData(-995,-995,0),
                MeshData(995,-995,0),
                MeshData(995,995,0),
                MeshData(-995,995,0)
        };

        return arenaMesh;
    }

public:
    static Entity* getEntity(){
        Entity* arena = new Entity();

        MeshComponent* arenaMeshRender = new MeshComponent();
            arenaMeshRender->setMesh(getModel());
        arena->addComponent(arenaMeshRender);

        arena->setPosition(Vector3(0,0,0));

        return arena;
    }

};


#endif //I3D_ARENAENTITY_H
