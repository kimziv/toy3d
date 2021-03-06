
#ifndef _TOY3D_RENDER_TARGET_H
#define _TOY3D_RENDER_TARGET_H

#include "Toy3DCommon.h"
#include "Toy3DPtrArray.h"
#include "Toy3DViewport.h"
#include "Toy3DRenderTargetListener.h"


TOY3D_BEGIN_NAMESPACE


    class RenderTarget
    {
    protected:
        TPtrArray *mViewportList;


    public:
        RenderTarget();
        virtual ~RenderTarget();

        virtual void update ();
        virtual Viewport* addViewport(Camera* cam, Uint left, Uint top, Uint width, Uint height);

        virtual void bind();
        virtual void unbind();

    private:

        TPtrArray mListeners;

        virtual void firePreUpdate();
        virtual void firePostUpdate();

    public:
        virtual void addListener (RenderTargetListener* listener);
        virtual void removeListener (RenderTargetListener* listener);
        virtual void removeAllListeners();

        Viewport* getViewport(Uint index) const;
    };



TOY3D_END_NAMESPACE

#endif
