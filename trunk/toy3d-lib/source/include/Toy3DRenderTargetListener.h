
#ifndef _TOY3D_RENDER_TARGET_LISTENER_H
#define _TOY3D_RENDER_TARGET_LISTENER_H

#include "Toy3DCommon.h"


TOY3D_BEGIN_NAMESPACE

    class RenderTargetListener 
    {


    public:
        virtual ~RenderTargetListener() {}

        virtual void preRenderTargetUpdate() 
        {return ;}

        virtual void postRenderTargetUpdate() 
        {return ;}

        virtual void preViewportUpdate() 
        {return ;}

        virtual void postViewportUpdate() 
        {return ;}

        virtual void viewportAdded() 
        {return ;}

        virtual void viewportRemoved() 
        {return ;}



    };



TOY3D_END_NAMESPACE

#endif
