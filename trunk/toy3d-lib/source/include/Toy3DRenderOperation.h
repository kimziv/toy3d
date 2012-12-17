
#ifndef _TOY3D_RENDER_OPERATION_H
#define _TOY3D_RENDER_OPERATION_H

#include "Toy3DCommon.h"

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
        void setVertices(Real *vertices, Uint count );
        void setColors(Real *colors, Uint count);
        void setUVs(Real *uvs, Uint count);
        void setNormals(Real *normals, Uint count);

        void setVertexIndex( Uint index);
        void setColorIndex( Uint index);
        void setUVIndex( Uint index);
        void setNormalIndex( Uint index);

        void setShaderAttribution (AttrConstantType type, Uint index);

        //return const 
        RenderMode getRenderMode();
        Real* getVertices();
        Real* getColors();
        Real* getUVs();
        Real* getNormals();

        Uint getVerticesCount();
        //Uint getColorsCount();
        //Uint getUVsCount();
        //Uint getNormalsCount();

        Uint getVertexIndex();
        Uint getColorIndex();
        Uint getUVIndex();
        Uint getNormalIndex();
    };


TOY3D_END_NAMESPACE

#endif
