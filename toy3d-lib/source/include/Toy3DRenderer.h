
#ifndef _TOY3D_RENDERER_H
#define _TOY3D_RENDERER_H

#include "Toy3DCommon.h"
#include "Toy3DRenderOperation.h"
#include "Toy3DShaderProgram.h"
#include "Toy3DAutoParamDataSource.h"
#include "Toy3DTextureUnitState.h"
#include "Toy3DPtrArray.h"
#include "Toy3DRenderTarget.h"
#include "Toy3DRenderWindow.h"
#include "Toy3DRenderTexture.h"


TOY3D_BEGIN_NAMESPACE


    class Renderer 
    {

    private:
        Real mProjectionMatrix[MATRIX_4x4_SIZE];
        Real mViewMatrix[MATRIX_4x4_SIZE];
        Real mWorldMatrix[MATRIX_4x4_SIZE];

        ShaderProgram* mCurrentShaderProgram;
        //Uint mTexUnitCapacity;


    public:
		Renderer ();
        ~Renderer ();

//        void useShaderProgram(Uint id);
        void bindShaderProgram(ShaderProgram *prog);
        void beginFrame(); 
        void render(RenderOperation *ro);
        void endFrame(); 

        void setWorldMatrix( Real matrix[MATRIX_4x4_SIZE] );
        void setProjectMatrix( Real matrix[MATRIX_4x4_SIZE] );
        void setViewMatrix( Real matrix[MATRIX_4x4_SIZE] );

        void setBackColor( Real r, Real g, Real b, Real a);
        void setViewPort(Uint x, Uint y, Uint width, Uint height);

        //void setDepthTest(Uint flag, Uint funcMode);

        //void setTexture(const Texture* tex);

        void updateAutoUniform (AutoParamDataSource *autoDataSource);
        void updateCustUniform ();

        /* blending operation switch*/
        void enableBlending(Bool flag);
        void setSceneBlending(BlendingFactor srcFactor,
            BlendingFactor destFactor, BlendingMode mode);

        void setTextureUnitSettings(TextureUnitState *texUnitState);

    private:
        Uint getRealRenderMode(RenderMode mode);

        /* convert blenging factor to the value which the hardware support. */
        Uint getRealBlendFactor(BlendingFactor srcFactor);
        /* convert blenging mode to the value which the hardware support. */
        Uint getRealBlendMode(BlendingMode mode);

        /* convert blenging factor to the value which the hardware support. */
        Uint getBlendFactor(BlendingFactor srcFactor);
        /* convert blenging mode to the value which the hardware support. */
        Uint getBlendMode(BlendingMode mode);

        Uint getRealTextureUnit(Uint texUnit);
        Uint getRealTextureType(TextureType target);
        Uint getRealTextureParameterName(TextureParameterName name);
        Uint getRealTextureParameterVal(TextureParameterVal val);

    private:
        TPtrArray *mRenderTargets;
        RenderTarget *mActiveRenderTarget;

    public:
        void setViewport(Viewport *vp);
        void setRenderTarget (RenderTarget *target);
        
        void updateAllRenderTargets ();

        RenderWindow* createRenderWindow ();
        RenderTexture* createRenderTexture (Texture *tex);

        void attachRenderTarget (RenderTarget *target); 
        void detachRenderTarget (RenderTarget *target); 


    };


TOY3D_END_NAMESPACE

#endif
