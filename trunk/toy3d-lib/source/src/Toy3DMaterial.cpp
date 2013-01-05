
#include "Toy3DMaterial.h"
#include "Toy3DTextureManager.h"


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

        //DELETEANDNULL(mShaderProgram);
        //DELETEANDNULL(mTexture);
    }

    Texture* Material::loadTexture(const char *pFileNmae)
    {
        return TextureManager::getInstance()->createTextureByFile(pFileNmae);
    }

    Texture* Material::createTexture(ImageInfo *pImageInfo)
    {
        return TextureManager::getInstance()->createTexture(pImageInfo);
    }

    Texture* Material::createTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp)
    {
        return TextureManager::getInstance()->createTexture(pImageData, width, height, bpp);
    }

    void Material::setShaderProgram (ShaderProgram *prog)
    {
       mShaderProgram = prog; 
    }

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
