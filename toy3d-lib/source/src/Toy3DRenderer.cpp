

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



//////////////////////////////////////////////////////////////////////////
//Renderer

    Renderer::Renderer() 
    {
        //MvGl2DemoMatrixIdentity( mProjectionMatrix );
        //MvGl2DemoMatrixIdentity( mViewMatrix );
    }

    Renderer::~Renderer() 
    {
    }

    //提供glDrawArrays、glDrawElements两种方式
    //目前只处理前一种方式
    void Renderer::render(RenderOperation *renderOp)
    {
        Uint mode;
        Uint index;

        if( !renderOp )
        {
            TOY3D_PRINT("render:NULL POINTER.\n", __FILE__, __LINE__);
            return;
        }

        //glUniformMatrix4fv(index, 1, 0, mWorldMatrix);
        //glUniformMatrix4fv(index, 1, 0, mProjectionMatrix);
        //glUniformMatrix4fv(index, 1, 0, mViewMatrix);

        //temp testing
        setForeground( 1.0f, 0.0f, 0.0f, 1.0f );

        switch( renderOp->getRenderMode() )
        {
        case TOY3D_POINTS:
            mode = GL_POINTS;
            break;

        case TOY3D_LINES:
            mode = GL_LINES;
            break;

        case TOY3D_LINE_STRIP:
            mode = TOY3D_LINE_STRIP;
            break;

        case TOY3D_TRIANGLES:
            mode = GL_TRIANGLES;
            break;

        case TOY3D_TRIANGLE_STRIP:
            mode = TOY3D_TRIANGLE_STRIP;
            break;

        case TOY3D_TRIANGLE_FAN:
            mode = GL_TRIANGLE_FAN;
            break;

        default:
            mode = 0;
            break;
        }

        if (mode)
        {
            index = renderOp->getVertexIndex();
            glVertexAttribPointer( index, 3, GL_FLOAT, 0, 0, renderOp->getVertex() );
            glEnableVertexAttribArray( index );
            glDrawArrays( GL_TRIANGLES, 0,  renderOp->getVerticesCount() );
        }

        return;
    }

    void Renderer::setWorldMatrix( Real matrix[MATRIX_4x4_SIZE] )
    {
        for ( int i=0; i<MATRIX_4x4_SIZE; i++)
        {
            mWorldMatrix[i] = matrix[i];
        }

        return;
    }

    void Renderer::setProjectMatrix(Real matrix[MATRIX_4x4_SIZE])
    {
        for ( int i=0; i<MATRIX_4x4_SIZE; i++)
        {
            mProjectionMatrix[i] = matrix[i];
        }

        return;
    }

    void Renderer::setViewMatrix(Real matrix[MATRIX_4x4_SIZE])
    {
        for ( int i=0; i<MATRIX_4x4_SIZE; i++)
        {
            mViewMatrix[i] = matrix[i];
        }

        return;
    }

    void Renderer::setViewPort(Uint x, Uint y, Uint width, Uint height)
    {
        glViewport( x, y, width, height);
        return;
    }

    void Renderer::setBackgroundColor( Real r, Real g, Real b, Real a)
    {
        glClearColor( r, g, b, a );
        return;
    }

    void Renderer::setForeground( Real r, Real g, Real b, Real a)
    {
        glClearColor( r, g, b, a );
        return;
    }

    void Renderer::setDepthTest(Uint flag, Uint funcMode)
    {
        return;
    }

    void Renderer::setBlend(Uint flag, Uint srcMode, Uint dstMode)
    {
        return;
    }

    void Renderer::setTexture(Uchar* name)
    {
        return;
    }

TOY3D_END_NAMESPACE
