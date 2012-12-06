
#ifndef _TOY3D_WORLD_H
#define _TOY3D_WORLD_H

#include "Toy3DCommon.h"
#include "Toy3DCamera.h"


TOY3D_BEGIN_NAMESPACE

	class World 
    {
	private:

        int     mWidth;
        int     mHeight;


	public:

		World ();
        ~World();

        void setMesh ();
        void startRendering ();

	};


TOY3D_END_NAMESPACE

#endif
