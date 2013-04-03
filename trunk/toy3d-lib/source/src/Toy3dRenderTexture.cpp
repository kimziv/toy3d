

#include "Toy3dRenderTexture.h"


TOY3D_BEGIN_NAMESPACE


//////////////////////////////////////////////////////////////////////////
// FrameBufferObject
    FrameBufferObject::FrameBufferObject()
    {
        mRBOId = -1;
        /* create fbo */
        glGenFramebuffers(1, &mFBOId);
    }

    FrameBufferObject::~FrameBufferObject ()
    {
        //delete rbo
        if (mRBOId >= 0)
            glDeleteRenderbuffers(1, (Uint *)&mRBOId);

        //delete fbo
        glDeleteFramebuffers(1, &mFBOId);
    }

    void FrameBufferObject::attachTexture(Uint textureId) 
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
        return;
    }
    
    void FrameBufferObject::attachDepthBuffer(Uint w, Uint h)
    {
        glGenRenderbuffers(1, (Uint *)&mRBOId);
        glBindRenderbuffer(GL_RENDERBUFFER, mRBOId);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, w, h);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRBOId);
        return;
    }

    Bool FrameBufferObject::checkStatus()
    {
        Uint status;

        status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if(status != GL_FRAMEBUFFER_COMPLETE)
        {
            printf(" status = 0x%x.\n", status);
            TOY3D_TIPS("FBO status is not complete. \n");
            return FALSE;
        }

        return TRUE;
    }

    void FrameBufferObject::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mFBOId);
    }

    void FrameBufferObject::unbind() 
    { 
        glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    }


//////////////////////////////////////////////////////////////////////////
// RenderTexture

    RenderTexture::RenderTexture()
    {
    }
    
    RenderTexture::~RenderTexture()
    {
    }
    
    Bool RenderTexture::init(Texture *tex)
    {
        mFBO.bind();
        mFBO.attachTexture (tex->getTextureID());
        mFBO.attachDepthBuffer(tex->getWidth(), tex->getHeight());
        return mFBO.checkStatus();
    }

    void RenderTexture::bind()
    {
        mFBO.bind();
    }
    
    void RenderTexture::unbind()
    {
        mFBO.unbind();
    }



TOY3D_END_NAMESPACE
