

#include "Toy3DRenderer.h"
#include "Toy3DMesh.h"

TOY3D_BEGIN_NAMESPACE



//////////////////////////////////////////////////////////////////////////
//RenderOperation
    RenderOperation::RenderOperation()
    {
    }

    RenderOperation::~RenderOperation()
    {
    }

    void RenderOperation::setRenderMode( RenderMode mode )
    {
        mRenderMode = mode;
        return;
    }

    void RenderOperation::setVertex(Real *vertices, Uint count )
    {
        if( !vertices || !count )
        {
            TOY3D_PRINT("NULL POINTER.\n", __FILE__, __LINE__);
            return;
        }

        mVertices = vertices;
        mVerticesCount = count;
        return;
    }

    void RenderOperation::setColor(Real *colors, Uint count)
    {
        if( !colors || !count )
        {
            TOY3D_PRINT("NULL POINTER.\n", __FILE__, __LINE__);
            return;
        }
        
        mColors = colors;
        //mColorsCount = count;
        return;
    }

    void RenderOperation::setUV(Real *uvs, Uint count)
    {
        if( !uvs || !count )
        {
            TOY3D_PRINT("NULL POINTER.\n", __FILE__, __LINE__);
            return;
        }
        
        mUVs = uvs;
        //mUVsCount = count;
        return;
    }

    void RenderOperation::setNormal(Real *normals, Uint count)
    {
        if( !normals || !count )
        {
            TOY3D_PRINT("NULL POINTER.\n", __FILE__, __LINE__);
            return;
        }
        
        mNormals = normals;
        //mNormalsCount = count;
        return;
    }
    
    void RenderOperation::setVertexIndex( Uint index)
    {
        mVertexIndex = index;
        return;
    }

    void RenderOperation::setColorIndex( Uint index)
    {
        mColorIndex = index;
        return;
    }

    void RenderOperation::setUVIndex( Uint index)
    {
        mUVIndex = index;
        return;
    }

    void RenderOperation::setNormalIndex( Uint index)
    {
        mNormalIndex = index;
        return;
    }

    RenderMode RenderOperation::getRenderMode()
    {
        return mRenderMode;
    }

    Real* RenderOperation::getVertex()
    {
        return mVertices;
    }

    Real* RenderOperation::getColor()
    {
        return mColors;
    }

    Real* RenderOperation::getUV()
    {
        return mUVs;
    }

    Real* RenderOperation::getNormal()
    {
        return mNormals;
    }

    Uint RenderOperation::getVerticesCount()
    {
        return mVerticesCount;
    }
/*
    Uint RenderOperation::getColorsCount()
    {
        return mColorsCount;
    }

    Uint RenderOperation::getUVsCount()
    {
        return mUVsCount;
    }

    Uint RenderOperation::getNormalsCount()
    {
        return mNormalsCount;
    }
*/
    Uint RenderOperation::getVertexIndex()
    {
        return mVertexIndex;
    }

    Uint RenderOperation::getColorIndex()
    {
        return mColorIndex;
    }

    Uint RenderOperation::getUVIndex()
    {
        return mUVIndex;
    }

    Uint RenderOperation::getNormalIndex()
    {
        return mNormalIndex;
    }

    void RenderOperation::setShaderAttribution (AttrConstantType type, Uint index)
    {
        switch(type) {

            case TOY3D_ATTR_VERTEX_INDEX:
                mVertexIndex = index;
                break;

            default:
                ;
        }
    }

TOY3D_END_NAMESPACE