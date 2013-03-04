
#include "Toy3DMaterial.h"
#include "Toy3DTextureManager.h"


TOY3D_BEGIN_NAMESPACE

    Material::Material() 
    {
        mShaderProgram = NULL;
        mTextureUnitStates = new TPtrArray();
        mTextureUnitStates->create();
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
        mTextureUnitStates->destroy();
        DELETEANDNULL(mTextureUnitStates);
        //mTexture = NULL;
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


/*
    void Material::setTexture (Texture *tex)
    {
        mTexture = tex;
    }
*/

    void Material::setShaderProgram (ShaderProgram *prog)
    {
        mShaderProgram = prog; 
    }

    ShaderProgram* Material::getShaderProgram ()
    {
        return mShaderProgram; 
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

    TextureUnitState* Material::createTextureUnitState(char *name)
    {
        TextureUnitState *texUS;

        texUS = searchTextureUnitState(name);
        if(texUS)
            return texUS;

        texUS = new TextureUnitState(name);
        if(!texUS)
            return NULL;

        if( mTextureUnitStates->append(texUS) )
            return texUS;
        
        DELETEANDNULL(texUS);
        return NULL;
    }

    Bool Material::addTextureUnitState(TextureUnitState *texUnitState)
    {
        if(texUnitState)
        {
            if( mTextureUnitStates->append(texUnitState) )
                return TRUE;
        }

        return FALSE;
    }

    TextureUnitState* Material::getTextureUnitState(char *name)
    {
        if(!name)
            return NULL;

        return searchTextureUnitState(name);
    }

    TextureUnitState* Material::getAllTextureUnitStates(Uint *count)
    {
        return (TextureUnitState* )(mTextureUnitStates->getAllElements(count));
    }

    TextureUnitState* Material::searchTextureUnitState(char *name) const
    {
        Uint i, count;
        TextureUnitState *texUS;

        count = mTextureUnitStates->getLength();
        for(i=0;i<count;i++)
        {
            texUS = (TextureUnitState *)mTextureUnitStates->getElement(i);
            if(strcmp(name, texUS->getName()))
                return texUS;
        }

        return NULL;
    }


TOY3D_END_NAMESPACE
