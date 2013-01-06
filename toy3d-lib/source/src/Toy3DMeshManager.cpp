#include "Toy3DMeshManager.h"

TOY3D_BEGIN_NAMESPACE


    MeshManager* MeshManager::mInstance = NULL;

    MeshManager::MeshManager()
    {
        mMeshCount = 0;
        for(int i=0; i<MAX_MESH_COUNT; i++)
        {
            mMeshs[i] = 0;
        }
    }

    MeshManager::~MeshManager()
    {
    }

    MeshManager* MeshManager::getInstance() 
    {
        if(NULL==mInstance)
            mInstance = new MeshManager();

        return mInstance;
    }

    Mesh* MeshManager::createMesh()
    {
        Mesh *pMesh = new Mesh();
        if( !pMesh )
            return NULL;

        mMeshs[mMeshCount++] = pMesh;
        
        return pMesh;
    }

    void MeshManager::destroyAllMeshes()
    {
        Mesh *temp;

        while(mMeshCount--)
        {
            temp = mMeshs[mMeshCount];
            delete temp;
            mMeshs[mMeshCount] = 0;
        }

        return;
    }


TOY3D_END_NAMESPACE
