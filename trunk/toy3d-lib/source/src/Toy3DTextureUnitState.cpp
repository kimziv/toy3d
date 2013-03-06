#include "Toy3DTextureUnitState.h"

TOY3D_BEGIN_NAMESPACE

    TextureUnitState::TextureUnitState()
    {
        mTextures = new TPtrArray();
        mTextures->create();
        //strncpy(mName, "", MAX_NAME_LEN);
        mName[strlen(mName)] = '\0';

        mType = T3D_TEXTURE_2D;
        mTexMinFilter = T3D_LINEAR;
        mTexMagFilter = T3D_LINEAR;
        mTexWrapS = T3D_CLAMP_TO_EDGE;
        mTexWrapT = T3D_CLAMP_TO_EDGE;

        return;
    }

    TextureUnitState::TextureUnitState(char *name)
    {
        mTextures = new TPtrArray();
        mTextures->create();

        if(name)
        {
            strncpy(mName, name, MAX_NAME_LEN);
        }
        mName[strlen(mName)] = '\0';

        mType       = T3D_TEXTURE_2D;
        mTexMinFilter = T3D_LINEAR;
        mTexMagFilter = T3D_LINEAR;
        mTexWrapS     = T3D_CLAMP_TO_EDGE;
        mTexWrapT     = T3D_CLAMP_TO_EDGE;

        return;
    }

    TextureUnitState::~TextureUnitState()
    {
        mTextures->destroy();
        DELETEANDNULL(mTextures);
        return;
    }

    void TextureUnitState::setName(char *name)
    {
        if(name)
        {
            strncpy(mName, name, MAX_NAME_LEN);
        }

        mName[strlen(mName)] = '\0';

        return;
    }

    void TextureUnitState::setID(Uint id)
    {
        mUnitID = id;
        return;
    }

    void TextureUnitState::setTexture(char *name)
    {
        //Fix me.
        printf("TextureUnitState::setTexture(chr *name) is not yet implemented.\n");
        return;
    }

    void TextureUnitState::setTexture(Texture *pTexture)
    {
        if(pTexture)
            mTextures->append(pTexture);

        return;
    }

    void TextureUnitState::removeTexture(Texture *pTexture)
    {
        if(pTexture)
            mTextures->remove(pTexture);

        return;
    }

    void TextureUnitState::setTextureType(TextureType target)
    {
        mType = target;
        return;
    }

    void TextureUnitState::setTextureParameter(
        TextureParameterName name, TextureParameterVal val)
    {
        switch(name)
        {
        case T3D_TEXTURE_MIN_FILTER:
            mTexMinFilter = val;
            break;
        case T3D_TEXTURE_MAG_FILTER:
            mTexMagFilter = val;
            break;
        case T3D_TEXTURE_WRAP_S:
            mTexWrapS = val;
            break;
        case T3D_TEXTURE_WRAP_T:
            mTexWrapT = val;
            break;
        }

        return;
    }

    void TextureUnitState::setTextureParameter(TextureParameterVal minFilterVal,
        TextureParameterVal magFilterVal,TextureParameterVal wrapSVal, TextureParameterVal wrapTVal)
    {
        mTexMinFilter = minFilterVal;
        mTexMagFilter = magFilterVal;
        mTexWrapS = wrapSVal;
        mTexWrapT = wrapTVal;

        return;
    }

    const char* TextureUnitState::getName()
    {
        return (const char *)mName;
    }

    const Uint TextureUnitState::getID()
    {
        return mUnitID;
    }

    TextureType TextureUnitState::getTextureType()
    {
        return mType;
    }

    TextureParameterVal TextureUnitState::getTextureParameter(TextureParameterName name)
    {
        switch(name)
        {
        case T3D_TEXTURE_MIN_FILTER:
            mTexMinFilter = mTexMinFilter;
            break;
        case T3D_TEXTURE_MAG_FILTER:
            mTexMagFilter = mTexMagFilter;
            break;
        case T3D_TEXTURE_WRAP_S:
            mTexWrapS = mTexWrapS;
            break;
        case T3D_TEXTURE_WRAP_T:
            mTexWrapT = mTexWrapT;
            break;
        }

        return mTexMinFilter;
    }

    void TextureUnitState::getTextureParameter(TextureParameterVal minFilterVal,
        TextureParameterVal magFilterVal,TextureParameterVal wrapSVal, TextureParameterVal wrapTVal)
    {
        minFilterVal = mTexMinFilter;
        magFilterVal = mTexMagFilter;
        wrapSVal = mTexWrapS;
        wrapTVal = mTexWrapT;
        
        return;
    }

    Uint TextureUnitState::getTextureCount()
    {
        return mTextures->getLength();
    }

    Uint TextureUnitState::getTextureSize()
    {
        return mTextures->getLength();
    }

    const Texture* TextureUnitState::getTextures(Uint index)
    {
        return (const Texture *)(mTextures->getElement(index));
    }



TOY3D_END_NAMESPACE