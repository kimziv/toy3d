#include "Toy3DMaterialManager.h"

TOY3D_BEGIN_NAMESPACE


    MaterialManager* MaterialManager::mInstance = NULL;

    MaterialManager::MaterialManager()
    {
        mMaterialCount = 0;
        for(int i=0; i<MAX_MATERIAL_COUNT; i++)
        {
            mMaterials[i] = 0;
        }
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
        Material *pMaterial = new Material();
        if( !pMaterial )
            return NULL;

        mMaterials[mMaterialCount++] = pMaterial;

        return pMaterial;
    }

    void MaterialManager::destroyAllMaterials()
    {
        Material *temp;

        while(mMaterialCount--)
        {
            temp = mMaterials[mMaterialCount];
            delete temp;
            mMaterials[mMaterialCount] = 0;
        }

        return;
    }


TOY3D_END_NAMESPACE
