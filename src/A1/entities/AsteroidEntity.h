//
// Created by dim on 24/03/2021.
//

#ifndef I3D_ASTEROIDENTITY_H
#define I3D_ASTEROIDENTITY_H


class AsteroidEntity {
private:
    static struct Mesh getModel() {
        struct Mesh mesh;
        mesh.mode = GL_TRIANGLE;
        mesh.data = {
                MeshData(-100, -100, 0),
                MeshData(100, -100, 0),
        };

        return mesh;
    }

public:
    static Entity* getEntity() {
        Entity* entity = new Entity();

        MeshComponent* meshRenderer = new MeshComponent();
        meshRenderer->setMesh(getModel());
        entity->addComponent(meshRenderer);

        ColliderComponent* col = new ColliderComponent(100, 200);
        col->setOffset(Vector3(100, 0, 0));

        entity->addComponent((Component*) col);

        return entity;
    }

};


#endif //I3D_ASTEROIDENTITY_H
