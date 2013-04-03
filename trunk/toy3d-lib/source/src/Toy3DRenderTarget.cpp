
#include "Toy3DRenderTarget.h"


TOY3D_BEGIN_NAMESPACE

    RenderTarget::RenderTarget()
    {
        mViewportList = new TPtrArray();
        mViewportList->create();

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



TOY3D_END_NAMESPACE
