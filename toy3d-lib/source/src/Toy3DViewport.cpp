
#include "Toy3DViewport.h"


TOY3D_BEGIN_NAMESPACE


    Viewport::Viewport(Camera* cam, RenderTarget* target, int left, int bottom, int width, int height)
        : mCamera(cam)
        , mTarget(target)
        , mLeft(left)
        , mBottom(bottom)
        , mWidth(width)
        , mHeight(height)
    {
    }

    Viewport::~Viewport()
    {
    }

    void Viewport::update(void)
    {
        if (mCamera)
        {
            // Tell Camera to render into me
            mCamera->renderScene(this);
        }
    }

    void Viewport::setLeft(Uint left)
    {
        mLeft = left;
        return;
    }

    void Viewport::setBottom(Uint bottom)
    {
        mBottom = bottom;
        return;
    }

    void Viewport::setWidth(Uint width)
    {
        mWidth = width;
        return;
    }

    void Viewport::setHeight(Uint height)
    {
        mHeight = height;
        return;
    }


TOY3D_END_NAMESPACE
