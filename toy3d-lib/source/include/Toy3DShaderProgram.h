
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
        ShaderProgramParams *mShaderParams;

    public:
        ShaderProgram();
        ~ShaderProgram();

        Uint loadShaderSource(const char *vertshader, const char *fragshader);
        Uint loadShaderBinary(const char* vertBinaryFile,
            Uint vertBFSize, const char* fragBinaryFile, Uint fragBFSize);

        void bindShaderParameters(ShaderProgramParams* pShaderPara);

        ShaderProgramParams* getShaderParameters();
        Uint getShaderProgramID();

        //get location from parameters
        int getAttrLocation(AttrConstantType type);

    private:
        void getShaderDebugInfo(Uint obj, GLenum status, const char* op);
        char* loadFile(const char *file);

        //get location from shader program
        int getAttrLocFromShader(const char *pName);
        int getUnifLocFromShader(const char *pName);

    };



TOY3D_END_NAMESPACE

#endif 
