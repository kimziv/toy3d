
#ifndef _TOY3D_VIEWPORT_H
#define _TOY3D_VIEWPORT_H

#include "Toy3DCommon.h"
#include "Toy3DCamera.h"
//#include "Toy3DRenderTarget.h"


TOY3D_BEGIN_NAMESPACE

    class RenderTarget;

    class Viewport
    {

    protected:
        Camera *mCamera;
        RenderTarget *mTarget;
        Uint mLeft, mTop, mWidth, mHeight;
        

    public:
        Viewport(Camera* camera, RenderTarget* target,
            int left, int top, int width, int height);

        virtual ~Viewport ();

        inline RenderTarget *getTarget () {return mTarget;}
        inline Uint getLeft () {return mLeft;}
        inline Uint getTop () {return mTop;}
        inline Uint getWidth () {return mWidth;}
        inline Uint getHeight () {return mHeight;}

    public:
        void update ();

    };



TOY3D_END_NAMESPACE

#endif
