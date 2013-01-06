#include "Toy3DShaderProgramManager.h"

TOY3D_BEGIN_NAMESPACE


    ShaderProgramManager* ShaderProgramManager::mInstance = NULL;

    ShaderProgramManager::ShaderProgramManager()
    {
        int i;
        mShaderProgramParamsCount = 0;
        for(i=0; i<MAX_SHADER_PROGRAM_PARAMS_COUNT; i++)
        {
            mShaderProgramParams[i] = 0;
        }

        mShaderProgramCount = 0;
        for(i=0; i<MAX_SHADER_PROGRAM_COUNT; i++)
        {
            mShaderPrograms[i] = 0;
        }
    }

    ShaderProgramManager::~ShaderProgramManager()
    {
    }

    ShaderProgramManager* ShaderProgramManager::getInstance() 
    {
        if(NULL==mInstance)
            mInstance = new ShaderProgramManager();

        return mInstance;
    }

    ShaderProgramParams* ShaderProgramManager::createShaderProgramParams()
    {
        ShaderProgramParams *pShaderProgramParams = new ShaderProgramParams();
        if( !pShaderProgramParams )
            return NULL;

        mShaderProgramParams[mShaderProgramParamsCount++] = pShaderProgramParams;
        
        return pShaderProgramParams;
    }

    ShaderProgram* ShaderProgramManager::createShaderProgram()
    {
        ShaderProgram *pShaderProgram = new ShaderProgram();
        if( !pShaderProgram )
            return NULL;

        mShaderPrograms[mShaderProgramCount++] = pShaderProgram;
        
        return pShaderProgram;
    }

    //void destroyShadrProgramParam(ShaderProgramParams *params);
    //void destroyShaderProgram(ShaderProgram *prog);

    void ShaderProgramManager::destroyAllShaderProgramParams()
    {
        ShaderProgramParams *temp;
        
        while(mShaderProgramParamsCount--)
        {
            temp = mShaderProgramParams[mShaderProgramParamsCount];
            delete temp;
            mShaderProgramParams[mShaderProgramParamsCount] = 0;
        }
        
        return;
    }

    void ShaderProgramManager::destroyAllShaderPrograms()
    {
        ShaderProgram *temp;

        while(mShaderProgramCount--)
        {
            temp = mShaderPrograms[mShaderProgramCount];
            delete temp;
            mShaderPrograms[mShaderProgramCount] = 0;
        }
        
        return;
    }


TOY3D_END_NAMESPACE
