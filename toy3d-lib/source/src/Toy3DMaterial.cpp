
#include "Toy3DMaterial.h"
#include "Toy3DTextureManager.h"


TOY3D_BEGIN_NAMESPACE

    Material::Material() 
    {
        mShaderProgram = NULL;
        mTexture = NULL;
        mAlphaBlending = FALSE;
    }


    Material::~Material() 
    {
        //FREEANDNULL(mShaderProgram);
        //FREEANDNULL(mTexture);

        /*
        if(mTexture)
        {
            Uint texid = mTexture->getTextureID();
            TextureManager::getInstance()->deleteTexture(&texid, 1);
            delete mTexture;
        }
        */
        mShaderProgram = NULL;
        mTexture = NULL;
    }

    /*
    Bool Material::loadTexture(const char *pFileNmae)
    {
        if(mTexture)
        {
            Uint texid = mTexture->getTextureID();
            TextureManager::getInstance()->deleteTexture(&texid, 1);
            delete mTexture;
        }

        mTexture = TextureManager::getInstance()->createTextureByFile(pFileNmae);
        if(mTexture)
            return TRUE;
        return FALSE;
    }

    Bool Material::createTexture(ImageInfo *pImageInfo)
    {
        if(mTexture)
        {
            Uint texid = mTexture->getTextureID();
            TextureManager::getInstance()->deleteTexture(&texid, 1);
            delete mTexture;
        }

        mTexture = TextureManager::getInstance()->createTexture(pImageInfo);
        if(mTexture)
            return TRUE;
        return FALSE;
    }

    Bool Material::createTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp)
    {
        if(mTexture)
        {
            Uint texid = mTexture->getTextureID();
            TextureManager::getInstance()->deleteTexture(&texid, 1);
            delete mTexture;
        }

        mTexture = TextureManager::getInstance()->createTexture(pImageData, width, height, bpp);
        if(mTexture)
            return TRUE;
        return FALSE;
    }
    */

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

    void Material::enableBlending(Bool flag)
    {
        mAlphaBlending = flag;
        return;
    }

    void Material::setSceneBlending(BlendingFactor srcFactor,
        BlendingFactor destFactor, BlendingMode mode)
    {
        mSrcFactor = srcFactor;
        mDestFactor = destFactor;
        mMode = mode;

        mAlphaBlending = TRUE;
        return;
    }

    const Bool Material::hasAlphaBlending() const
    {
        return (const Bool)mAlphaBlending;
    }

    const BlendingFactor Material::getSrcBlendFactor() const
    {
        return (const BlendingFactor)mSrcFactor;
    }

    const BlendingFactor Material::getDestBlendFactor() const
    {
        return (const BlendingFactor)mDestFactor;
    }

    const BlendingMode Material::getBlendMode() const
    {
        return (const BlendingMode)mMode;
    }



TOY3D_END_NAMESPACE
