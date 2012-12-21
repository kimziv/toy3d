
#ifndef _TOY3D_TEXTURE_MANAGER_H
#define _TOY3D_TEXTURE_MANAGER_H

#include "Toy3DCommon.h"
#include "Toy3DTexture.h"



TOY3D_BEGIN_NAMESPACE

    typedef struct _ImageInfo
    {
        Uint width;        // width of image
        Uint height;       // height of image
        Uint bpp;          // bytes per pixel
        char *pImageData;   // image data
        Uint size;          // image data len (should be equal to width*height*bpp )
    }ImageInfo;

    class TextureManager
    {
    private:
        TextureManager();

    protected:
        static TextureManager* mInstance;

    public:
        ~TextureManager();
        static TextureManager* getInstance();

        Texture* createTexture(ImageInfo *pImageInfo);
        Texture* createTextureByFile( const char* fileName );

        //void useTexture(Uint texid);
        void deleteTexture(Uint *texids, Uint count);
    };


TOY3D_END_NAMESPACE

#endif
