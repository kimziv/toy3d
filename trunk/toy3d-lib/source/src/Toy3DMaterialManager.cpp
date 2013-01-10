#include "Toy3DMaterialManager.h"

TOY3D_BEGIN_NAMESPACE


    MaterialManager* MaterialManager::mInstance = NULL;

    MaterialManager::MaterialManager()
    {
        mPtrArray = new TPtrArray();
        mPtrArray->create();
    }

    MaterialManager::~MaterialManager()
    {
    }

    MaterialManager* MaterialManager::getInstance() 
    {
        if(NULL==mInstance)
            mInstance = new MaterialManager();

        return mInstance;
    }

    Material* MaterialManager::createMaterial()
    {
        Bool rv;
        Material *pMaterial = new Material();
        if( !pMaterial )
            return NULL;

        rv = mPtrArray->append((TPointer)pMaterial);
        if(FALSE==rv)
        {
            DELETEANDNULL(pMaterial);
            TOY3D_TIPS("Error: Failed to store the pointer.\n");
            return NULL;
        }

        return pMaterial;
    }

    void MaterialManager::destroyAllMaterials()
    {
        Material *temp;
        Uint length = mPtrArray->getLength();

        while(length--)
        {
            temp = (Material *)mPtrArray->getElement(length);
            DELETEANDNULL(temp);
            //mPtrArray->setElement(NULL, length);
        }
        
        mPtrArray->destroy();
        DELETEANDNULL(mPtrArray);

        return;
    }


TOY3D_END_NAMESPACE
