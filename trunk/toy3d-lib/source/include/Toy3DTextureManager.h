
#ifndef _TOY3D_TEXTURE_MANAGER_H
#define _TOY3D_TEXTURE_MANAGER_H

#include "Toy3DCommon.h"
#include "Toy3DTexture.h"



TOY3D_BEGIN_NAMESPACE

    class TextureManager
    {
    private:
        TextureManager();

    protected:
        static TextureManager* mInstance;

    public:
        ~TextureManager();
        static TextureManager* getInstance();

        /* function : createTexture
         * parameter:
         *     pImageData : color data of image
         *     width : width of image
         *     height : height of image
         *     bpp : bytes per pixel
         * warning : the memory of pImageData be released.
         */
        Texture* createTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp);

        Texture* createTexture(ImageInfo *pImageInfo);

        Texture* createTextureByFile( const char* fileName );

        //void useTexture(Uint texid);
        void deleteTexture(Uint *texids, Uint count);
    };


TOY3D_END_NAMESPACE

#endif
