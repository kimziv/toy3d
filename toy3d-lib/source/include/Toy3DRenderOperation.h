
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
        void setVertex(Real *vertices, Uint count );
        void setColor(Real *colors, Uint count);
        void setUV(Real *uvs, Uint count);
        void setNormal(Real *normals, Uint count);

        void setVertexIndex( Uint index);
        void setColorIndex( Uint index);
        void setUVIndex( Uint index);
        void setNormalIndex( Uint index);

        void setShaderAttribution (AttrConstantType type, Uint index);

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


TOY3D_END_NAMESPACE

#endif
