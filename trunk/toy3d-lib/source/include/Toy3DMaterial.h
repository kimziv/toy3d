
#ifndef _TOY3D_MATERIAL_H
#define _TOY3D_MATERIAL_H

#include "Toy3DCommon.h"
#include "Toy3DShaderProgram.h"
#include "Toy3DTexture.h"


TOY3D_BEGIN_NAMESPACE


    class Material 
    {

    private:
        Texture *mTexture;
        ShaderProgram* mShaderProgram;


    public:
        Material();
        ~Material();

    public:

        Bool loadTexture(const char *pFileNmae);
        //Bool createTexture(ImageInfo *pImageInfo);
        //Bool createTexture(unsigned  char *pImageData, Uint width, Uint height, Uint bpp);
        void setTexture(Texture* tex);
        void setShaderProgram (ShaderProgram *prog);

        const Texture* getTexture();
        ShaderProgram* getShaderProgram ();
    };



TOY3D_END_NAMESPACE

#endif
