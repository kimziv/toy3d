
#include "Toy3DMaterial.h"


TOY3D_BEGIN_NAMESPACE

    Material::Material() 
    {
        mShaderProgram = NULL;
        mTexture = NULL;
    }


    Material::~Material() 
    {
        FREEANDNULL(mShaderProgram);
        FREEANDNULL(mTexture);
    }


    void Material::setShaderProgram (ShaderProgram *prog)
    {
       mShaderProgram = prog; 
    }

    ShaderProgram* Material::getShaderProgram ()
    {
       return mShaderProgram; 
    }



    void Material::setTexture (Texture *tex)
    {
        mTexture = tex;
    }




TOY3D_END_NAMESPACE
