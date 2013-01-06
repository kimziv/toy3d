
#ifndef _TOY3D_MATERIAL_MANAGER_H
#define _TOY3D_MATERIAL_MANAGER_H

#include "Toy3DCommon.h"
#include "Toy3DMaterial.h"



TOY3D_BEGIN_NAMESPACE

    class MaterialManager
    {
    private:
        MaterialManager();
        static MaterialManager* mInstance;

        Material *mMaterials[MAX_MATERIAL_COUNT];
        Uint mMaterialCount;

    public:
        ~MaterialManager();
        static MaterialManager* getInstance();

        Material* createMaterial();

        Material* createMaterial(ImageInfo *pImageInfo);
        Material* createMaterialByFile( const char* fileName );

        //void destroyMaterial(Material *mat);
        void destroyAllMaterials();
    };


TOY3D_END_NAMESPACE

#endif
