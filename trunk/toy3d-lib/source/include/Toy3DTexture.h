
#ifndef _TOY3D_TEXTURE_H
#define _TOY3D_TEXTURE_H

#include "Toy3DCommon.h"
#include "Toy3DImage.h"

TOY3D_BEGIN_NAMESPACE

    class Texture
    {
    private:
        
    protected:
        Uint mTextureID;
        //char mName[32];

    public:
        Texture();
        ~Texture();

        Bool genTexture(Image *image);
        Bool genTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp);
        void setParameter();
        const Uint getTextureID() const;

    };


TOY3D_END_NAMESPACE

#endif
