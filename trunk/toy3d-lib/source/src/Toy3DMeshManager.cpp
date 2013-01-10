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
        //or
        //mPtrArray[mPtrArray->getLength()] = pMesh;
        //or
        //mPtrArray->insert((TPointer)pMesh, mPtrArray->getLength());

        return pMesh;
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

        mPtrArray->destroy();
        DELETEANDNULL(mPtrArray);

        return;
    }


TOY3D_END_NAMESPACE
