
#ifndef _TOY3D_TEXTURE_UNIT_STATE_H
#define _TOY3D_TEXTURE_UNIT_STATE_H

#include "Toy3DCommon.h"
#include "Toy3DTexture.h"
#include "Toy3DPtrArray.h"

TOY3D_BEGIN_NAMESPACE

enum TextureType
{
    T3D_TEXTURE_1D,
    T3D_TEXTURE_2D,
    T3D_TEXTURE_3D
};

enum TextureParameterName
{
    T3D_TEXTURE_MIN_FILTER,
    T3D_TEXTURE_MAG_FILTER,
    T3D_TEXTURE_WRAP_S,
    T3D_TEXTURE_WRAP_T
    //GL_TEXTURE_WRAP_R /*for 3D texture */
};

enum TextureParameterVal
{
    /* The following parameters are applicable to T3D_TEXTURE_MAG_FILTER. */
    T3D_NEAREST,
    T3D_LINEAR,

    /* The following parameters are applicable to T3D_TEXTURE_MAG_FILTER and T3D_TEXTURE_MIN_FILTER. */
    T3D_NEAREST_MIPMAP_NEAREST,
    T3D_LINEAR_MIPMAP_NEAREST,
    T3D_NEAREST_MIPMAP_LINEAR,
    T3D_LINEAR_MIPMAP_LINEAR,

    /* The following parameters are applicable to T3D_TEXTURE_WRAP_S and T3D_TEXTURE_WRAP_T. */
    T3D_REPEAT,
    T3D_CLAMP_TO_EDGE,
    T3D_MIRRORED_REPEAT
};

/*
typedef struct _TextureParameter
{
    TextureTarget       target;
    TextureParameterVal texMinFilter;
    TextureParameterVal texMagFilter;
    TextureParameterVal texWrapS;
    TextureParameterVal texWrapT;
}TextureParameter;
*/

class TextureUnitState
{
private:
    char       mName[MAX_NAME_LEN+1];
    Uint       mUnitID;
    TPtrArray  *mTextures;

    TextureType         mType;
    TextureParameterVal mTexMinFilter;
    TextureParameterVal mTexMagFilter;
    TextureParameterVal mTexWrapS;
    TextureParameterVal mTexWrapT;

protected:

public:
    TextureUnitState();
    TextureUnitState(char *name);
    ~TextureUnitState();

    void setName(char *name);
    void setID(Uint id);

    void setTexture(char *name);
    void setTexture(Texture *pTexture);
    void removeTexture(Texture *pTexture);

    void setTextureType(TextureType target);
    void setTextureParameter(TextureParameterName name, TextureParameterVal val);
    void setTextureParameter(TextureParameterVal minFilterVal,
        TextureParameterVal magFilterVal,TextureParameterVal wrapSVal, TextureParameterVal wrapTVal);

    const char* getName();
    const Uint getID();
    TextureType getTextureType();
    TextureParameterVal getTextureParameter(TextureParameterName name);
    void getTextureParameter(TextureParameterVal minFilterVal,
        TextureParameterVal magFilterVal,TextureParameterVal wrapSVal, TextureParameterVal wrapTVal);

    Uint getTextureCount();
    //const Texture* getTextures(char *name);
    const Texture* getAllTextures(Uint *count);
};



TOY3D_END_NAMESPACE

#endif
