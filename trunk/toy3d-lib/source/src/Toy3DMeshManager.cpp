#include "Toy3DMeshManager.h"

TOY3D_BEGIN_NAMESPACE


    MeshManager* MeshManager::mInstance = NULL;

    MeshManager::MeshManager()
    {
        mPtrArray = new TPtrArray();
        mPtrArray->create();
    }

    MeshManager::~MeshManager()
    {
        mPtrArray->destroy();
        DELETEANDNULL(mPtrArray);
    }

    MeshManager* MeshManager::getInstance() 
    {
        if(NULL==mInstance)
            mInstance = new MeshManager();

        return mInstance;
    }

    Mesh* MeshManager::createMesh()
    {
        Bool rv;
        Mesh *pMesh = new Mesh();
        if( !pMesh )
            return NULL;

        rv = mPtrArray->append((TPointer)pMesh );
        if(FALSE==rv)
        {
            DELETEANDNULL(pMesh);
            TOY3D_TIPS("Error: Failed to store the pointer.\n");
            return NULL;
        }

        return pMesh;
    }

    void MeshManager::destroyMesh(Mesh *pMesh)
    {
        mPtrArray->remove((TPointer)pMesh);
        DELETEANDNULL(pMesh);
        return;
    }

    void MeshManager::destroyAllMeshes()
    {
        Mesh *temp;
        Uint length = mPtrArray->getLength();
        
        while(length--)
        {
            temp = (Mesh *)mPtrArray->getElement(length);
            DELETEANDNULL(temp);
            //mPtrArray->setElement(NULL, length);
        }

        mPtrArray->clearAll();

        return;
    }


TOY3D_END_NAMESPACE
