

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

        mVerticesCount = 0;
        mVertexIndex = 0;
        mColorIndex = 0;
        mUVIndex = 0;
        mNormalIndex = 0;
        //mTextureID = 0;
    }

    RenderOperation::~RenderOperation()
    {
        mVertices = NULL;
        mColors = NULL;
        mUVs = NULL;
        mNormals = NULL;

        mVerticesCount = 0;
        mVertexIndex = 0;
        mColorIndex = 0;
        mUVIndex = 0;
        mNormalIndex = 0;
        //mTextureID = 0;
    }

    void RenderOperation::setRenderMode( RenderMode mode )
    {
        mRenderMode = mode;
        return;
    }

    void RenderOperation::setVertices(Real *pVertices, Uint count)
    {
        mVertices = pVertices;
        mVerticesCount = count;
        return;
    }

    void RenderOperation::setColors(Real *pColors)
    {
        mColors = pColors;
        return;
    }

    void RenderOperation::setUVs(Real *pUVs)
    {
        mUVs = pUVs;
        return;
    }

    void RenderOperation::setNormals(Real *pNormals)
    {
        mNormals = pNormals;
        return;
    }

/*
    void RenderOperation::setTextureID(Uint texID)
    {
        mTextureID = texID;
        return;
    }

    void RenderOperation::setTextureInfo( Uint texID, Uint texUnit)
    {
        mTextureID = texID;
        mTextureUnit = texUnit;
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

    /*
    Uint RenderOperation::getTextureID()
    {
        return mTextureID;
    }

    Uint RenderOperation::getTextureUnit()
    {
        return mTextureUnit;
    }

    void RenderOperation::setShaderAttrLocation (AttrConstantType type, Uint index)
    {
        switch(type)
        {
        case TOY3D_ATTR_VERTEX:
            mVertexIndex = index;
            break;

        case TOY3D_ATTR_COLOR:
            mColorIndex = index;
            break;

        case TOY3D_ATTR_UV:
            mUVIndex = index;
            break;

        case TOY3D_ATTR_NORMAL:
            mNormalIndex = index;
            break;

        default:
            ;
        }
    }

    Uint RenderOperation::getShaderAttrLocation(AttrConstantType type)
    {
        switch( type )
        {
        case TOY3D_ATTR_VERTEX:
            return mVertexIndex;

        case TOY3D_ATTR_COLOR:
            return mColorIndex;

        case TOY3D_ATTR_UV:
            return mUVIndex;

        case TOY3D_ATTR_NORMAL:
            return mNormalIndex;

        default:
            return 0;
        }
    }
    */

TOY3D_END_NAMESPACE
