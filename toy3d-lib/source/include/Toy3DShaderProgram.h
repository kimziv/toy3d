
#ifndef _TOY3D_SHADER_PROGRAM_H
#define _TOY3D_SHADER_PROGRAM_H


#include <stdio.h>
#include <stdlib.h>


#include "Toy3DCommon.h"
#include "Toy3DShaderProgramParams.h"

TOY3D_BEGIN_NAMESPACE

    class ShaderProgram
    {
    protected:
        Uint mShaderProgramID;
        ShaderProgramParams* mShaderParams;

    public:
        ShaderProgram();
        ~ShaderProgram();

        Uint loadShaderSource(const char *vertshader, const char *fragshader);
        Uint loadShaderBinary(const char* vertBin, Uint vertBinSize, const char* fragBin, Uint fragBinSize);
        void bindShaderParameters(ShaderProgramParams* pShaderPara);
        Uint getShaderProgramID();
        ShaderProgramParams* getShaderParameters();

    private:
        void getShaderDebugInfo(Uint obj, GLenum status, const char* op);
        char* loadFile(const char *file);

/*
        void shaderLogMessage(const char* message, ...);

        //‘›”√
        void MvGl2DemoShaderDebug(Uint obj, GLenum status, const char* op);
        Uint ShaderProgram::MvGl2DemoLoadShaderSources(
            const char* vertFile,
            const char* fragFile,
            boolean debugging);
        Uint MvGl2DemoLoadShaderBinaries(
            const char* vertBin, Uint vertBinSize,
            const char* fragBin, Uint fragBinSize,
                                   GLboolean debugging);
        char* MvGl2DemoLoadFile(const char *file);
*/
    };



TOY3D_END_NAMESPACE

#endif 
