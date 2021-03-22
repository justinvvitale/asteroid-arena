//
// Created by dim on 21/03/2021.
//

#ifndef I3D_TESTENTITY_H
#define I3D_TESTENTITY_H


class TestEntity {
private:
    static struct Mesh getModel(){
        struct Mesh mesh;
        mesh.mode = GL_LINE_LOOP;
        mesh.data = {
                MeshData(-100,-100,0),
                MeshData(100,-100,0),
                MeshData(100,100,0),
                MeshData(-100,100,0)
        };

        return mesh;
    }

public:
    static Entity* getEntity(){
        Entity* entity = new Entity();

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getModel());
        entity->addComponent(meshRenderer);

        entity->addComponent((Component*)new ColliderComponent(100));

        return entity;
    }

};


#endif //I3D_TESTENTITY_H
