
#ifndef _TOY3D_SHADER_PROGRAM_MANAGER_H
#define _TOY3D_SHADER_PROGRAM_MANAGER_H

#include "Toy3DCommon.h"
#include "Toy3DShaderProgram.h"
#include "Toy3DShaderProgramParams.h"



TOY3D_BEGIN_NAMESPACE

    class ShaderProgramManager
    {
    private:
        ShaderProgramManager();
        static ShaderProgramManager* mInstance;

        ShaderProgramParams *mShaderProgramParams[MAX_SHADER_PROGRAM_PARAMS_COUNT];
        ShaderProgram *mShaderPrograms[MAX_SHADER_PROGRAM_COUNT];

        Uint mShaderProgramParamsCount;
        Uint mShaderProgramCount;

    public:
        ~ShaderProgramManager();
        static ShaderProgramManager* getInstance();

        ShaderProgramParams* createShaderProgramParams();
        ShaderProgram* createShaderProgram();

        //void destroyShadrProgramParam(ShaderProgramParams *params);
        //void destroyShaderProgram(ShaderProgram *prog);
        void destroyAllShaderProgramParams();
        void destroyAllShaderPrograms();
    };


TOY3D_END_NAMESPACE

#endif
