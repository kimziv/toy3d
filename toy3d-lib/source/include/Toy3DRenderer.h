
#ifndef _TOY3D_RENDERER_H
#define _TOY3D_RENDERER_H

#include "Toy3DCommon.h"
#include "Toy3DMesh.h"

TOY3D_BEGIN_NAMESPACE

    class Renderer 
    {

    private:
        Real mProjectionMatrix[MATRIX_4x4_SIZE];
        Real mViewMatrix[MATRIX_4x4_SIZE];
        Real mWorldMatrix[MATRIX_4x4_SIZE];


    public:
		Renderer ();
        ~Renderer ();

        void render(Mesh* mesh);

        void setWorldMatrix( Real matrix[MATRIX_4x4_SIZE] );
        void setProjectMatrix( Real matrix[MATRIX_4x4_SIZE] );
        void setViewMatrix( Real matrix[MATRIX_4x4_SIZE] );

        void setBackgroundColor( Real r, Real g, Real b, Real a);
        void setForeground( Real r, Real g, Real b, Real a);
        void setViewPort(Uint x, Uint y, Uint width, Uint height);

        void setDepthTest(Uint flag, Uint funcMode);
        void setBlend(Uint flag, Uint srcMode, Uint dstMode);
        void setTexture(Uchar* name);
    };


TOY3D_END_NAMESPACE

#endif
