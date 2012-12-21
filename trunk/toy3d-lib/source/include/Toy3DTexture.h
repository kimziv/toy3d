
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

        //void loadImage(Image  *image);
        void genTexture(Image *image);
        void setParameter();
        const Uint getTextureID() const;

    };


TOY3D_END_NAMESPACE

#endif
