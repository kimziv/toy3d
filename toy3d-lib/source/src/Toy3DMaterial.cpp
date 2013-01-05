
#include "Toy3DMaterial.h"


TOY3D_BEGIN_NAMESPACE

    Material::Material() 
    {
        mShaderProgram = NULL;
        mTexture = NULL;
    }


    Material::~Material() 
    {
        //FREEANDNULL(mShaderProgram);
        //FREEANDNULL(mTexture);

        DELETEANDNULL(mShaderProgram);
        DELETEANDNULL(mTexture);
    }

    /*
     * The pointer must bu created by new.
     * And you don't need to delete it after this call.
     */
    void Material::setShaderProgram (ShaderProgram *prog)
    {
       mShaderProgram = prog; 
    }

    /*
     * The pointer must bu created by new.
     * And you don't need to delete it after this call.
     */
    void Material::setTexture (Texture *tex)
    {
        mTexture = tex;
    }

    ShaderProgram* Material::getShaderProgram ()
    {
        return mShaderProgram; 
    }

    const Texture* Material::getTexture()
    {
        return (const Texture*)mTexture;
    }



TOY3D_END_NAMESPACE
