
#ifndef _TOY3D_RENDERER_H
#define _TOY3D_RENDERER_H

#include "Toy3DCommon.h"
#include "Toy3DMesh.h"

TOY3D_BEGIN_NAMESPACE

    class RenderOperation
    {
    protected:
        Real *mVertices;
        Real *mColors;
        Real *mUVs;
        Real *mNormals;

        Uint mVertexIndex;
        Uint mColorIndex;
        Uint mUVIndex;
        Uint mNormalIndex;

        Uint mVerticesCount;
        //Uint mColorsCount;
        //Uint mUVsCount;
        //Uint mNormalsCount;

        RenderMode mRenderMode;

    public:
        RenderOperation();
        ~RenderOperation();

        void setRenderMode( RenderMode mode );
        void setVertex(Real *vertices, Uint count );
        void setColor(Real *colors, Uint count);
        void setUV(Real *uvs, Uint count);
        void setNormal(Real *normals, Uint count);

        void setVertexIndex( Uint index);
        void setColorIndex( Uint index);
        void setUVIndex( Uint index);
        void setNormalIndex( Uint index);

        RenderMode getRenderMode();
        Real* getVertex();
        Real* getColor();
        Real* getUV();
        Real* getNormal();

        Uint getVerticesCount();
        //Uint getColorsCount();
        //Uint getUVsCount();
        //Uint getNormalsCount();

        Uint getVertexIndex();
        Uint getColorIndex();
        Uint getUVIndex();
        Uint getNormalIndex();
    };

    class Renderer 
    {

    private:
        Real mProjectionMatrix[MATRIX_4x4_SIZE];
        Real mViewMatrix[MATRIX_4x4_SIZE];
        Real mWorldMatrix[MATRIX_4x4_SIZE];


    public:
		Renderer ();
        ~Renderer ();

        void render(RenderOperation *renderOp);

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
