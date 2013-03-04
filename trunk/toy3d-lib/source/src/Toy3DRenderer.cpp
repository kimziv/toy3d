

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
        int  index = 0;
        Real *pTempR = 0;
        //Uint texUnit;

        if( !ro )
        {
            TOY3D_PRINT("render:NULL POINTER.", __FILE__, __LINE__);
            return;
        }

        mode = getRealRenderMode(ro->getRenderMode());
        if (!mode)
        {
            TOY3D_TIPS("Error: no RenderMode data.\n");
            return;
        }

        //vertex
        //index = ro->getShaderAttribution( TOY3D_ATTR_VERTEX_INDEX );
        pTempR = ro->getVertices();
        if(pTempR)
        {
            index = mCurrentShaderProgram->getAttrLocation(TOY3D_ATTR_VERTEX);
            glVertexAttribPointer(index, 3, GL_FLOAT, 0, 0, pTempR);
            glEnableVertexAttribArray(index);
        }
        else
        {
            TOY3D_TIPS("Error: no vertices data.\n");
            return;
        }
        
        //color
        pTempR = ro->getColors();
        if( pTempR )
        {
            index = mCurrentShaderProgram->getAttrLocation(TOY3D_ATTR_COLOR);
            glVertexAttribPointer(index, 4, GL_FLOAT, 0, 0, pTempR);
            glEnableVertexAttribArray(index);
        }
        
        //uv
        pTempR = ro->getUVs();
        if( pTempR )
        {
            index = mCurrentShaderProgram->getAttrLocation(TOY3D_ATTR_UV);
            glVertexAttribPointer( index, 2, GL_FLOAT, 0, 0, pTempR );
            glEnableVertexAttribArray( index );
        }
        
        //normals
        pTempR = ro->getNormals();
        if( pTempR )
        {
            index = mCurrentShaderProgram->getAttrLocation(TOY3D_ATTR_NORMAL);
            glVertexAttribPointer( index, 3, GL_FLOAT, 0, 0, pTempR );
            glEnableVertexAttribArray( index );
        }

        glDrawArrays( mode, 0,  ro->getVerticesCount() );

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

    Uint Renderer::getRealRenderMode(RenderMode mode)
    {
        Uint glMode;

        switch( mode )
        {
        case TOY3D_POINTS:
            glMode = GL_POINTS;
            break;
            
        case TOY3D_LINES:
            glMode = GL_LINES;
            break;
            
        case TOY3D_LINE_STRIP:
            glMode = TOY3D_LINE_STRIP;
            break;
            
        case TOY3D_TRIANGLES:
            glMode = GL_TRIANGLES;
            break;
            
        case TOY3D_TRIANGLE_STRIP:
            glMode = GL_TRIANGLE_STRIP;
            break;
            
        case TOY3D_TRIANGLE_FAN:
            glMode = GL_TRIANGLE_FAN;
            break;
            
        default:
            glMode = 0;
            break;
        }

        return glMode;
    }

    void Renderer::updateAutoUniform(AutoParamDataSource* autoUniformData)
    {

        if (mCurrentShaderProgram)
            mCurrentShaderProgram->getShaderParameters()->updateAutoUniformConst (autoUniformData);

        return;
    }

    void Renderer::updateCustUniform()
    {

        if (mCurrentShaderProgram)
            mCurrentShaderProgram->getShaderParameters()->updateCustUniformConst ();

        return;
    }

    void Renderer::enableBlending(Bool flag)
    {
        if(flag)
        {
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
        }
        else
        {
            glEnable(GL_DEPTH_TEST);
            glDisable(GL_BLEND);
        }

        return;
    }

    void Renderer::setSceneBlending(
        BlendingFactor srcFactor, BlendingFactor destFactor, BlendingMode mode)
    {
        glBlendFunc(getRealBlendFactor(srcFactor), getRealBlendFactor(destFactor));
        glBlendEquation(getRealBlendMode(mode));

        return;
    }

    void Renderer::setTextureUnitSettings(Uint unit, TextureUnitState* texUnitState)
    {
        Uint target;
        Uint parameterName;
        int  parameterVal;
        Uint count, i;
        const Texture *tex;

        /* active the texture unit */
        glActiveTexture( getRealTextureUnit(unit) );

        /* get the target */
        target = getRealTextureTarget(texUnitState->getTextureTarget());

        /* set parameters */
        parameterName = getRealTextureParameterName(T3D_TEXTURE_MAG_FILTER);
        parameterVal = getRealTextureParameterVal(
            texUnitState->getTextureParameter(T3D_TEXTURE_MAG_FILTER));
        glTexParameteri(target, parameterName, parameterVal);

        parameterName = getRealTextureParameterName(T3D_TEXTURE_MIN_FILTER);
        parameterVal = getRealTextureParameterVal(
            texUnitState->getTextureParameter(T3D_TEXTURE_MIN_FILTER));
        glTexParameteri(target, parameterName, parameterVal);

        parameterName = getRealTextureParameterName(T3D_TEXTURE_WRAP_S);
        parameterVal = getRealTextureParameterVal(
            texUnitState->getTextureParameter(T3D_TEXTURE_WRAP_S));
        glTexParameteri(target, parameterName, parameterVal);

        parameterName = getRealTextureParameterName(T3D_TEXTURE_WRAP_T);
        parameterVal = getRealTextureParameterVal(texUnitState->getTextureParameter(T3D_TEXTURE_WRAP_T));
        glTexParameteri(target, parameterName, parameterVal);

        /* bind each texture */
        tex = texUnitState->getAllTextures(&count);
        for(i=0;i<count;i++)
        {
            glBindTexture(target, tex->getTextureID());
            tex++;
        }

        return;
    }

    Uint Renderer::getRealBlendFactor(BlendingFactor factor)
    {
        switch(factor)
        {
        case T3D_ONE:
            return GL_ONE;
        case T3D_ZERO:
            return GL_ZERO;
        case T3D_DST_COLOR:
            return GL_DST_COLOR;
        case T3D_SRC_COLOR:
            return GL_SRC_COLOR;
        case T3D_ONE_MINUS_DST_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
        case T3D_ONE_MINUS_SRC_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
        case T3D_DST_ALPHA:
            return GL_DST_ALPHA;
        case T3D_SRC_ALPHA:
            return GL_SRC_ALPHA;
        case T3D_ONE_MINUS_DST_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
        case T3D_ONE_MINUS_SRC_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
        case T3D_SRC_ALPHA_SATURATE:
            return GL_SRC_ALPHA_SATURATE;
        }
        
        return GL_ONE;
    }
    
    Uint Renderer::getRealBlendMode(BlendingMode mode)
    {
        switch(mode)
        {
        case T3D_ADD:
            return GL_FUNC_ADD;
        case T3D_SUBTRACT:
            return GL_FUNC_SUBTRACT;
        case T3D_REVERSE_SUBTRACT:
            return GL_FUNC_REVERSE_SUBTRACT;
        case T3D_MIN:
            return GL_MIN_EXT;
        case T3D_MAX:
            return GL_MAX;
        }
        
        return GL_FUNC_ADD;
    }

    int Renderer::getRealTextureUnit(Uint texUnit)
    {
        if(texUnit>MAX_TEXTURE_UNIT)
            return -1;
        return gTextureUnit[texUnit];
    }

    Uint Renderer::getRealTextureTarget(TextureTarget target)
    {
        switch(target)
        {
        case T3D_TEXTURE_1D:
            return GL_TEXTURE_1D;

        case T3D_TEXTURE_2D:
            return GL_TEXTURE_2D;

        case T3D_TEXTURE_3D:
            return GL_TEXTURE_3D;
        }

        return GL_TEXTURE_2D;
    }

    Uint Renderer::getRealTextureParameterName(TextureParameterName name)
    {
        switch(name)
        {
        case T3D_TEXTURE_MIN_FILTER:
            return GL_TEXTURE_MIN_FILTER;

        case T3D_TEXTURE_MAG_FILTER:
            return GL_TEXTURE_MAG_FILTER;

        case T3D_TEXTURE_WRAP_S:
            return GL_TEXTURE_WRAP_S;

        case T3D_TEXTURE_WRAP_T:
            return GL_TEXTURE_WRAP_T;
        }

        return GL_TEXTURE_MIN_FILTER;
    }

    int  Renderer::getRealTextureParameterVal(TextureParameterVal val)
    {
        switch(val)
        {
        case T3D_NEAREST:
            return GL_NEAREST;
            
        case T3D_LINEAR:
            return GL_LINEAR;
            
        case T3D_NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
            
        case T3D_LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;

        case T3D_NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;

        case T3D_LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;

        case T3D_CLAMP:
            return GL_CLAMP;

        case T3D_REPEAT:
            return GL_REPEAT;

        case T3D_MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        }
        
        return GL_NEAREST;
    }





    Uint Renderer::getBlendFactor(BlendingFactor factor)
    {
        switch(factor)
        {
        case T3D_ONE:
            return GL_ONE;
        case T3D_ZERO:
            return GL_ZERO;
        case T3D_DST_COLOR:
            return GL_DST_COLOR;
        case T3D_SRC_COLOR:
            return GL_SRC_COLOR;
        case T3D_ONE_MINUS_DST_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
        case T3D_ONE_MINUS_SRC_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
        case T3D_DST_ALPHA:
            return GL_DST_ALPHA;
        case T3D_SRC_ALPHA:
            return GL_SRC_ALPHA;
        case T3D_ONE_MINUS_DST_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
        case T3D_ONE_MINUS_SRC_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
        case T3D_SRC_ALPHA_SATURATE:
            return GL_SRC_ALPHA_SATURATE;
        }
        
        return GL_ONE;
    }


    Uint Renderer::getBlendMode(BlendingMode mode)
    {
        switch(mode)
        {
        case T3D_ADD:
            return GL_FUNC_ADD;
        case T3D_SUBTRACT:
            return GL_FUNC_SUBTRACT;
        case T3D_REVERSE_SUBTRACT:
            return GL_FUNC_REVERSE_SUBTRACT;
        case T3D_MIN:
            return GL_MIN_EXT;
        case T3D_MAX:
            return GL_MAX;
        }

        return GL_FUNC_ADD;
    }



TOY3D_END_NAMESPACE

