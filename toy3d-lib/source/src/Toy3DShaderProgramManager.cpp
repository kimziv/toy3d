#include "Toy3DShaderProgramManager.h"

TOY3D_BEGIN_NAMESPACE


    ShaderProgramManager* ShaderProgramManager::mInstance = NULL;

    ShaderProgramManager::ShaderProgramManager()
    {
        mShaderPtrArray = new TPtrArray();
        mShaderPtrArray->create();

        mShaderParamsPtrArray = new TPtrArray();
        mShaderParamsPtrArray->create();
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
        Bool rv;
        ShaderProgramParams *pShaderProgramParams = new ShaderProgramParams();
        if( !pShaderProgramParams )
            return NULL;

        rv = mShaderParamsPtrArray->append( (TPointer)pShaderProgramParams );
        if(FALSE==rv)
        {
            DELETEANDNULL(pShaderProgramParams)
            TOY3D_TIPS("Error: Failed to store the pointer.\n");
            return NULL;
        }

        return pShaderProgramParams;
    }

    ShaderProgram* ShaderProgramManager::createShaderProgram()
    {
        Bool rv;
        ShaderProgram *pShaderProgram = new ShaderProgram();
        if( !pShaderProgram )
            return NULL;

        rv = mShaderPtrArray->append( (TPointer)pShaderProgram );
        if(FALSE==rv)
        {
            DELETEANDNULL(pShaderProgram);
            TOY3D_TIPS("Error: Failed to store the pointer.\n");
            return NULL;
        }

        return pShaderProgram;
    }

    //void destroyShadrProgramParam(ShaderProgramParams *params);
    //void destroyShaderProgram(ShaderProgram *prog);

    void ShaderProgramManager::destroyAllShaderProgramParams()
    {
        ShaderProgramParams *temp;
        Uint length = mShaderParamsPtrArray->getLength();

        while(length--)
        {
            temp = (ShaderProgramParams *)mShaderParamsPtrArray->getElement(length);
            DELETEANDNULL(temp);
            //mPtrArray->setElement(NULL, length);
        }
        
        mShaderParamsPtrArray->destroy();
        DELETEANDNULL(mShaderParamsPtrArray);

        return;
    }

    void ShaderProgramManager::destroyAllShaderPrograms()
    {
        ShaderProgram *temp;
        Uint length = mShaderPtrArray->getLength();
        
        while(length--)
        {
            temp = (ShaderProgram *)mShaderPtrArray->getElement(length);
            DELETEANDNULL(temp);
            //mPtrArray->setElement(NULL, length);
        }
        
        mShaderPtrArray->destroy();
        DELETEANDNULL(mShaderPtrArray);

        return;
    }


TOY3D_END_NAMESPACE
