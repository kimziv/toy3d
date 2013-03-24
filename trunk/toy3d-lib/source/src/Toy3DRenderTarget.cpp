
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
        for (int i = 0; i < mViewportList->getLength(); i++)
        {
            Viewport *vp = (Viewport*)mViewportList->getElement(i);
            delete vp;
        }

        mViewportList->destroy();
        delete mViewportList;

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
        for (int i = 0; i < mViewportList->getLength(); i++){
            Viewport *vp = (Viewport*)mViewportList->getElement(i);
            vp->update();
        }
    }



TOY3D_END_NAMESPACE
