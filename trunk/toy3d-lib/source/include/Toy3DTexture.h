
#ifndef _TOY3D_TEXTURE_H
#define _TOY3D_TEXTURE_H

#include "Toy3DCommon.h"
#include "Toy3DImage.h"

TOY3D_BEGIN_NAMESPACE

#if 0

/*
 *  the definition of texture
 *  the base operation of texture :load, generate, degenerate, unload.
 */
class Texture 
{
    enum TextureLoadingState
    {
        TOY3D_UNLOADED,
        TOY3D_LOADED,
        //TOY3D_UNGENERATED,//this state maybe unnecessary.
        TOY3D_GENERATED
    };

    /*
    enum TextureParameterName
    {
        GL_TEXTURE_MAG_FILTER,
        GL_TEXTURE_MIN_FILTER,
        GL_TEXTURE_WRAP_S,
        GL_TEXTURE_WRAP_T
    };

    enum TextureParameterVal
    {
        GL_NEAREST,
        GL_LINEAR,
        GL_NEAREST_MIPMAP_NEAREST,
        GL_LINEAR_MIPMAP_NEAREST,
        GL_NEAREST_MIPMAP_LINEAR,
        GL_LINEAR_MIPMAP_LINEAR,
        GL_CLAMP,
        GL_REPEAT;
    };

    enum TextureDataType
    {
        GL_BYTE,
        GL_UNSIGNED_BYTE,
        GL_SHORT,
        GL_UNSIGNED_SHORT,
        GL_INT,
        GL_UNSIGNED_INT,
        GL_FLOAT,
        GL_FIXED
    };

    enum PixelFormat
    {
        GL_DEPTH_COMPONENT,
        GL_ALPHA,
        GL_RGB,
        GL_RGBA,
        GL_LUMINANCE,
        GL_LUMINANCE_ALPHA
    };

    typedef struct _TextureParameter
    {
        TextureParameterName paraName;
        TextureParameterVal paraVal;
        TextureDataType dataType;
        PixelFormat format;
    }TextureParameter;
    /*

    private:

    protected:
        /* the base member */
        char mName[MAX_NAME_LEN_BIG+1]; /* the resource file name */
        //char mFileName[MAX_NAME_LEN_BIG+1];

        Uint mTextureID;
        Uint mWidth;
        Uint mHeight;
        Uint mBytesPerPixel;
        unsigned char *mPixelData;

        //TextureParameter mParameter;

        /* the extended member */
        Bool mIsResident;
        volatile Uint mIdleLevel;
        volatile TextureLoadingState mLoadingState;
        volatile Bool mIsBeingUsed;

    public:
        //Texture();
        //Texture(char *pFileName);
        Texture(char *pFileName, Bool isResident = FALSE);
        ~Texture();

        /* 
         * The interfaces are used for textures created by the constructor with more than one parameter.
         */
        //Bool load();
        /*
         * The interface is used for textures created by the constructor with one parameter.
         */
        //Bool load(char *pFileName);
        Bool load(Image *image);
        Bool load(unsigned char *pImageData, Uint width, Uint height, Uint bytesPerPixel);

        Bool unload();

        Bool generate();
        Bool degenerate();

        void setIdleLevel(Uint value);

        const Bool isResident() const;
        const Bool getUsingState() const;
        const TextureLoadingState getLoadingState() const;
        const Uint getIdleLevel() const;

        const Uint getTextureID() const;
        const char* getTextureName() const;
        const char* getTextureResFileName() const;
}

#endif

    class Texture
    {
    private:
        Uint mTextureID;
        Uint mWidth;
        Uint mHeight;
        Uint mBytesPerPixel;
        //unsigned char *mPixelData;

    protected:
        //char mName[32];

    public:
        Texture();
        ~Texture();

        Bool genTexture(Image *image);
        Bool genTexture(unsigned char *pImageData, Uint width, Uint height, Uint bytesPerPixel);

        void setParameter();

        Uint getTextureID() const;
        Uint getWidth() const;
        Uint getHeight() const;
        Uint getBytesPerPixel() const;
    };


TOY3D_END_NAMESPACE

#endif
