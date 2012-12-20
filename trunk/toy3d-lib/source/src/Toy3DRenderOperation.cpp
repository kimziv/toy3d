

#include "Toy3DRenderer.h"
#include "Toy3DMesh.h"

TOY3D_BEGIN_NAMESPACE



//////////////////////////////////////////////////////////////////////////
//RenderOperation
    RenderOperation::RenderOperation()
    {
        mVertices = NULL;
        mColors = NULL;
        mUVs = NULL;
        mNormals = NULL;
        mVerticesCount = NULL;
    }

    RenderOperation::~RenderOperation()
    {
        mVertices = NULL;
        mColors = NULL;
        mUVs = NULL;
        mNormals = NULL;
        mVerticesCount = NULL;
    }

    void RenderOperation::setRenderMode( RenderMode mode )
    {
        mRenderMode = mode;
        return;
    }

    void RenderOperation::setVertices(Real *vertices, Uint count )
    {
        if( !vertices || !count )
        {
            TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
            return;
        }

        mVertices = vertices;
        mVerticesCount = count;
        return;
    }

    void RenderOperation::setColors(Real *colors, Uint count)
    {
        if( !colors || !count )
        {
            TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
            return;
        }
        if( count != mVerticesCount )
        {
            TOY3D_PRINT("Colors array length error.", __FILE__, __LINE__);
            return;
        }
        
        mColors = colors;
        //mColorsCount = count;
        return;
    }

    void RenderOperation::setUVs(Real *uvs, Uint count)
    {
        if( !uvs || !count )
        {
            TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
            return;
        }
        
        mUVs = uvs;
        //mUVsCount = count;
        return;
    }

    void RenderOperation::setNormals(Real *normals, Uint count)
    {
        if( !normals || !count )
        {
            TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
            return;
        }
        
        mNormals = normals;
        //mNormalsCount = count;
        return;
    }

    void RenderOperation::setTextureID( Uint id )
    {
        mTextureID = id;
    }
/*
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
*/
    RenderMode RenderOperation::getRenderMode()
    {
        return mRenderMode;
    }

    Real* RenderOperation::getVertices()
    {
        return mVertices;
    }

    Real* RenderOperation::getColors()
    {
        return mColors;
    }

    Real* RenderOperation::getUVs()
    {
        return mUVs;
    }

    Real* RenderOperation::getNormals()
    {
        return mNormals;
    }

    Uint RenderOperation::getVerticesCount()
    {
        return mVerticesCount;
    }

    Uint RenderOperation::getTextureID()
    {
        return mTextureID;
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
*/
    void RenderOperation::setShaderAttribution (AttrConstantType type, Uint index)
    {
        switch(type)
        {
        case TOY3D_ATTR_VERTEX_INDEX:
            mVertexIndex = index;
            break;

        case TOY3D_ATTR_COLOR_INDEX:
            mColorIndex = index;
            break;

        case TOY3D_ATTR_UV_INDEX:
            mUVIndex = index;
            break;

        case TOY3D_ATTR_NORMAL_INDEX:
            mNormalIndex = index;
            break;

        default:
            ;
        }
    }

    Uint RenderOperation::getShaderAttribution(AttrConstantType type)
    {
        switch( type )
        {
        case TOY3D_ATTR_VERTEX_INDEX:
            return mVertexIndex;

        case TOY3D_ATTR_COLOR_INDEX:
            return mColorIndex;

        case TOY3D_ATTR_UV_INDEX:
            return mUVIndex;

        case TOY3D_ATTR_NORMAL_INDEX:
            return mNormalIndex;

        default:
            return 0;
        }
    }

TOY3D_END_NAMESPACE
