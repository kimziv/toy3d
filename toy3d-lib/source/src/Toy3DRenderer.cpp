

#include "Toy3DRenderer.h"
#include "Toy3DMesh.h"

TOY3D_BEGIN_NAMESPACE

//Maybe need to modify according to the actual situation of the hardware.
#define MAX_TEXTURE_UNIT 32
static int gTextureUnit[MAX_TEXTURE_UNIT] = {
    GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2,GL_TEXTURE3, GL_TEXTURE4,
    GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9,
    GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14,
    GL_TEXTURE15, GL_TEXTURE16, GL_TEXTURE17, GL_TEXTURE18, GL_TEXTURE19,
    GL_TEXTURE20, GL_TEXTURE21, GL_TEXTURE22, GL_TEXTURE23, GL_TEXTURE24,
    GL_TEXTURE25, GL_TEXTURE26, GL_TEXTURE27, GL_TEXTURE28, GL_TEXTURE29,
    GL_TEXTURE30, GL_TEXTURE31};

//////////////////////////////////////////////////////////////////////////
//Renderer

    Renderer::Renderer() 
    {
 
        mCurrentShaderProgram = NULL;

        //MvGl2DemoMatrixIdentity( mProjectionMatrix );
        //MvGl2DemoMatrixIdentity( mViewMatrix );
    }

    Renderer::~Renderer() 
    {
    }

    void Renderer:: bindShaderProgram(ShaderProgram *prog)
    {
        mCurrentShaderProgram = prog;

        Uint id = mCurrentShaderProgram->getShaderProgramID();
        glUseProgram(id);
    }
/*
    void Renderer:: useShaderProgram(Uint id)
    {
        glUseProgram(id);
    }
*/

    void Renderer::beginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }


    void Renderer::endFrame()
    {
    }

    
    void Renderer::render(RenderOperation *ro)
    {
        Uint mode = 0;
        int index = 0;
        Real *pTempR = 0;
        Uint texUnit;

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
            //index = ro->getShaderAttribution( TOY3D_ATTR_VERTEX_INDEX );
            index = mCurrentShaderProgram->getAttrLocation( TOY3D_ATTR_VERTEX );

#if 0
            printf ("index = %d. vertex count = %d.\n", index, ro->getVerticesCount());       
            int i = 0;
            Real *data = ro->getVertex();
            for (i = 0; i < ro->getVerticesCount() * 3;i++)
                printf ("%f,", data[i]);
            printf ("\n");
#endif

            //vertex
            glVertexAttribPointer( index, 3, GL_FLOAT, 0, 0, ro->getVertices() );
            glEnableVertexAttribArray( index );

            //color
/*
            //uvs
            pTempR = ro->getUVs();
            if( pTempR )
            {
                glEnable(GL_TEXTURE_2D);
                texUnit = ro->getTextureUnit();
                if(texUnit>MAX_TEXTURE_UNIT)
                {
                    TOY3D_TIPS("Error: texture unit is beyond the supported scope.\n");
                }
                glActiveTexture(gTextureUnit[texUnit]);
                glBindTexture(GL_TEXTURE_2D, ro->getTextureID());
                //printf("tex id = %d\n", ro->getTextureID());
                index = ro->getShaderAttribution( TOY3D_ATTR_UV );
                glVertexAttribPointer( index, 2, GL_FLOAT, 0, 0, pTempR );
                glEnableVertexAttribArray( index );
            }
*/
            //normals

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

/*
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
*/


    void Renderer::updateAutoUniform(AutoParamDataSource* autoUniformData)
    {

        if (mCurrentShaderProgram)
            mCurrentShaderProgram->getShaderParameters()->updateAutoUniformConst (autoUniformData);

    }

    void Renderer::updateCustUniform()
    {

        if (mCurrentShaderProgram)
            mCurrentShaderProgram->getShaderParameters()->updateCustUniformConst ();

    }


TOY3D_END_NAMESPACE
