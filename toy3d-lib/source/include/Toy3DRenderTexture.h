
#ifndef _TOY3D_RENDER_TEXTURE_H
#define _TOY3D_RENDER_TEXTURE_H

#include "Toy3DCommon.h"
#include "Toy3DTexture.h"
#include "Toy3DRenderTarget.h"



TOY3D_BEGIN_NAMESPACE


//////////////////////////////////////////////////////////////////////////
// FrameBufferObject

    class FrameBufferObject
    {
    private:
        //FBOManager *mManager;
        Uint mFBOId;
        int mRBOId;

    public:
        FrameBufferObject();
        ~FrameBufferObject();

        void bind();
        void unbind();

        void attachDepthBuffer(Uint w, Uint h);
        void attachTexture(Uint textureId);

        Bool checkStatus();

        //Uint getFboid() const;
        //int getRboid() const;
    };


//////////////////////////////////////////////////////////////////////////
// RenderTexture

    class RenderTexture : public RenderTarget
    {
	private:
        FrameBufferObject mFBO;

    public:
		RenderTexture();
        ~RenderTexture();

        Bool init(Texture *tex);
        void bind();
        void unbind();
	};



TOY3D_END_NAMESPACE

#endif
