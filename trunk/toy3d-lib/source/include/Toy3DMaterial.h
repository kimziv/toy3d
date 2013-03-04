
#ifndef _TOY3D_MATERIAL_H
#define _TOY3D_MATERIAL_H

#include "Toy3DCommon.h"
#include "Toy3DShaderProgram.h"
#include "Toy3DTextureUnitState.h"


TOY3D_BEGIN_NAMESPACE

    class Material 
    {
    private:
        //Texture *mTexture;
        ShaderProgram* mShaderProgram;
        TPtrArray*     mTextureUnitStates;

        Bool           mAlphaBlending;
        BlendingFactor mSrcFactor;
        BlendingFactor mDestFactor;
        BlendingMode   mMode;

        Bool searchTextureUnitState(char *name) const;

    public:
        Material();
        ~Material();

        //Bool loadTexture(const char *pFileNmae);
        //Bool createTexture(ImageInfo *pImageInfo);
        //Bool createTexture(unsigned  char *pImageData, Uint width, Uint height, Uint bpp);

        TextureUnitState* createTextureUnitState(char *name);
        Bool addTextureUnitState(TextureUnitState *texUnitState);
        TextureUnitState* getTextureUnitState(char *name);
        TextureUnitState* getAllTextureUnitStates(Uint *count);

        void setShaderProgram (ShaderProgram *prog);
        ShaderProgram* getShaderProgram ();

        const Bool hasAlphaBlending() const;

        void setSceneBlending(BlendingFactor srcFactor,
            BlendingFactor destFactor, BlendingMode mode = T3D_ADD);

        const BlendingFactor getSrcBlendFactor() const;
        const BlendingFactor getDestBlendFactor() const;
        const BlendingMode getBlendMode() const;

    };



TOY3D_END_NAMESPACE

#endif
