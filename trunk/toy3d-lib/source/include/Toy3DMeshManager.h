
#ifndef _TOY3D_MESH_MANAGER_H
#define _TOY3D_MESH_MANAGER_H

#include "Toy3DCommon.h"
#include "Toy3DMesh.h"
#include "Toy3DPtrArray.h"



TOY3D_BEGIN_NAMESPACE

    class MeshManager
    {
    private:
        MeshManager();
        static MeshManager* mInstance;

        //Mesh *mMeshs[MAX_MESH_COUNT];
        //Uint mMeshCount;
        TPtrArray *mPtrArray;

    public:
        ~MeshManager();
        static MeshManager* getInstance();

        Mesh* createMesh();
        void destroyMesh(Mesh *pMesh);
        void destroyAllMeshes();
        Mesh* getMesh(const char *pName);
    };


TOY3D_END_NAMESPACE

#endif
