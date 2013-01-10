
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
        //Uint mTextureID;
        //Uint mTextureUnit;

        RenderMode mRenderMode;

    public:
        RenderOperation();
        ~RenderOperation();

        void setRenderMode( RenderMode mode );
        void setVertices(Real *pVertices, Uint count );
        //void setColors(Real *colors, Uint count);
        //void setUVs(Real *uvs, Uint count);
        //void setNormals(Real *normals, Uint count);

        /*
         * The data security is ensured by Mesh itself.
         * That means we think that all data got from Mesh is safe, 
         */
        void setColors(Real *pColors);
        void setUVs(Real *pUVs);
        void setNormals(Real *pNormals);

        //void setTextureInfo( Uint texID, Uint texUnit);
        //void setShaderAttrLocation (AttrConstantType type, Uint index);

        //return const 
        RenderMode getRenderMode();
        Real* getVertices();
        Real* getColors();
        Real* getUVs();
        Real* getNormals();

        Uint getVerticesCount();
        //Uint getTextureID();
        //Uint getTextureUnit();

        //Uint getShaderAttrLocation(AttrConstantType type);
    };


TOY3D_END_NAMESPACE

#endif
