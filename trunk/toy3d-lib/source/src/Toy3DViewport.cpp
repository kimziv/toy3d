
#include "Toy3DViewport.h"


TOY3D_BEGIN_NAMESPACE


    Viewport::Viewport(Camera* cam, RenderTarget* target, int left, int top, int width, int height)
        : mCamera(cam)
        , mTarget(target)
        , mLeft(left)
        , mTop(top)
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




TOY3D_END_NAMESPACE
