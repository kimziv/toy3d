
#ifndef _TOY3D_RENDER_TARGET_H
#define _TOY3D_RENDER_TARGET_H

#include "Toy3DCommon.h"
#include "Toy3DPtrArray.h"
#include "Toy3DViewport.h"


TOY3D_BEGIN_NAMESPACE


    class RenderTarget
    {

    protected:
        TPtrArray *mViewportList;


    public:
        RenderTarget ();
        virtual ~RenderTarget ();

    public:
        virtual void update ();
        virtual Viewport* addViewport(Camera* cam, Uint left, Uint top, Uint width, Uint height);



    };



TOY3D_END_NAMESPACE

#endif
