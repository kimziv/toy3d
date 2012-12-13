

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

    void Renderer:: useShaderProgram(Uint id)
    {
        glUseProgram(id);
    }

    void Renderer::beginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }


    void Renderer::endFrame()
    {
    }

    
    void Renderer::render(RenderOperation *ro)
    {
        Uint mode;
        Uint index;

        if( !ro )
        {
            TOY3D_PRINT("render:NULL POINTER.", __FILE__, __LINE__);
            return;
        }

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
            mode = GL_TRIANGLE_STRIP;
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

#if 0
            printf ("index = %d. vertex count = %d.\n", index, ro->getVerticesCount());       
            int i = 0;
            Real *data = ro->getVertex();
            for (i = 0; i < ro->getVerticesCount() * 3;i++)
                printf ("%f,", data[i]);
            printf ("\n");
#endif

            glVertexAttribPointer( index, 3, GL_FLOAT, 0, 0, ro->getVertex() );
            glEnableVertexAttribArray( index );

            glDrawArrays( mode, 0,  ro->getVerticesCount() );
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

    void Renderer::setBackColor( Real r, Real g, Real b, Real a)
    {
        glClearColor( r, g, b, a );
        return;
    }


    void Renderer::setDepthTest(Uint flag, Uint funcMode)
    {
        //temp testing
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
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
