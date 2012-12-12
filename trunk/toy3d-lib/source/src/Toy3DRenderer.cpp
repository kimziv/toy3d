

#include "Toy3DRenderer.h"
#include "Toy3DMesh.h"

TOY3D_BEGIN_NAMESPACE




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
    void Renderer::render(RenderOperation *ro)
    {
        Uint mode;
        Uint index;

        if( !ro )
        {
            TOY3D_PRINT("render:NULL POINTER.\n", __FILE__, __LINE__);
            return;
        }

        //glUniformMatrix4fv(index, 1, 0, mWorldMatrix);
        //glUniformMatrix4fv(index, 1, 0, mProjectionMatrix);
        //glUniformMatrix4fv(index, 1, 0, mViewMatrix);

        //temp testing
        setForeground( 1.0f, 0.0f, 0.0f, 1.0f );

        switch( ro->getRenderMode() )
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
            index = ro->getVertexIndex();
            glVertexAttribPointer( index, 3, GL_FLOAT, 0, 0, ro->getVertex() );
            glEnableVertexAttribArray( index );
            glDrawArrays( GL_TRIANGLES, 0,  ro->getVerticesCount() );
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
