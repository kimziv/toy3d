
#ifndef _TOY3D_SHADER_PROGRAM_MANAGER_H
#define _TOY3D_SHADER_PROGRAM_MANAGER_H

#include "Toy3DCommon.h"
#include "Toy3DShaderProgram.h"
#include "Toy3DShaderProgramParams.h"
#include "Toy3DPtrArray.h"


TOY3D_BEGIN_NAMESPACE

    class ShaderProgramManager
    {
    private:
        ShaderProgramManager();
        static ShaderProgramManager* mInstance;

        TPtrArray *mShaderPtrArray;
        TPtrArray *mShaderParamsPtrArray;

    public:
        ~ShaderProgramManager();
        static ShaderProgramManager* getInstance();

        ShaderProgramParams* createShaderProgramParams();
        ShaderProgram* createShaderProgram();

        void destroyOneParam(ShaderProgramParams *pShaderParam);
        void destroyOneProg(ShaderProgram *pShaderProgram);
        void destroyAllShaderProgramParams();
        void destroyAllShaderPrograms();
    };


TOY3D_END_NAMESPACE

#endif
