
#include "Toy3DRenderTarget.h"


TOY3D_BEGIN_NAMESPACE

    RenderTarget::RenderTarget()
    {
        mViewportList = new TPtrArray();
        mViewportList->create();

        mListeners.create();

    }

    RenderTarget::~RenderTarget()
    {
        // Delete viewports
        for (Uint i = 0; i < mViewportList->getLength(); i++)
        {
            Viewport *vp = (Viewport*)mViewportList->getElement(i);
            DELETEANDNULL(vp);
        }

        mViewportList->destroy();
        DELETEANDNULL(mViewportList);

       
        mListeners.destroy();
    }

    Viewport* RenderTarget::addViewport(Camera* cam, Uint left, Uint top ,
        Uint width , Uint height)
    {
        Viewport* vp = new Viewport(cam, this, left, top, width, height);

        mViewportList->append((void*)vp);

        return vp;
    }

    void RenderTarget::update ()
    {
        for (Uint i = 0; i < mViewportList->getLength(); i++){
            Viewport *vp = (Viewport*)mViewportList->getElement(i);
            vp->update();
        }
    }

    void RenderTarget::bind()
    {
        return;
    }

    void RenderTarget::unbind()
    {
        return;
    }

    void RenderTarget::firePreUpdate()
    {
        for (int i = 0; i < mListeners.getLength(); i++) {
            RenderTargetListener *listener = (RenderTargetListener*)mListeners.getElement(i);
            listener->preRenderTargetUpdate();
        }

    }

    void RenderTarget::firePostUpdate()
    {
        for (int i = 0; i < mListeners.getLength(); i++) {
            RenderTargetListener *listener = (RenderTargetListener*)mListeners.getElement(i);
            listener->postRenderTargetUpdate();
        }

    }



    void RenderTarget::addListener(RenderTargetListener* listener)
    {
        mListeners.append((void*)listener);
    }

    void RenderTarget::removeListener(RenderTargetListener* listener)
    {
        mListeners.remove((void*)listener);
    }


    void RenderTarget::removeAllListeners()
    {
         //remove from array. user free the 
         for (int i = mListeners.getLength() - 1; i>=0; i--) {
            RenderTargetListener *listener = (RenderTargetListener*)mListeners.getElement(i);
            mListeners.remove(listener);
        }
       
    }



TOY3D_END_NAMESPACE
