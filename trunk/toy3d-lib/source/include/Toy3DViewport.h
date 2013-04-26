
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
        Uint mLeft, mBottom, mWidth, mHeight;
        

    public:
        Viewport(Camera* camera, RenderTarget* target,
            int left, int bottom, int width, int height);

        virtual ~Viewport ();

        inline RenderTarget *getTarget () {return mTarget;}
        inline Uint getLeft () {return mLeft;}
        inline Uint getBottom () {return mBottom;}
        inline Uint getWidth () {return mWidth;}
        inline Uint getHeight () {return mHeight;}

        void setLeft(Uint left);
        void setBottom(Uint bottom);
        void setWidth(Uint width);
        void setHeight(Uint height);

    public:
        void update ();

    };



TOY3D_END_NAMESPACE

#endif
