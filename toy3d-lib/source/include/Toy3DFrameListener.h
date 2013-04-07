
#ifndef _TOY3D_FRAME_LISTENER_H
#define _TOY3D_FRAME_LISTENER_H

#include "Toy3DCommon.h"


TOY3D_BEGIN_NAMESPACE

    class FrameListener 
    {


    public:
        virtual ~FrameListener() {}

        virtual bool frameStarted() 
        {return TRUE;}

        virtual bool frameEnded() 
        {return TRUE;}


    };



TOY3D_END_NAMESPACE

#endif
