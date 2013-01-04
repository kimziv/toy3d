
#include "Toy3DShaderProgram.h"
#include "Toy3DShaderProgramParams.h"
#include <sys/stat.h>
#include <stdarg.h>


TOY3D_BEGIN_NAMESPACE

ShaderProgram::ShaderProgram()
{
    mShaderParams = 0;
    mShaderProgramID = 0;
}

ShaderProgram::~ShaderProgram()
{
    if( mShaderProgramID )
    {
        glDeleteShader(mShaderProgramID);
        mShaderProgramID = 0;
    }

    //if(mShaderParams)
    //    delete mShaderParams;
}

int ShaderProgram::getAttrLocFromShader(const char *pName)
{
    return glGetAttribLocation(mShaderProgramID, (const char *)pName);
}

int ShaderProgram::getUnifLocFromShader(const char *pName)
{
    return glGetUniformLocation(mShaderProgramID, (const char *)pName);
}

void ShaderProgram::bindShaderParameters(ShaderProgramParams* pShaderPara)
{
    Uint count, i;
    const char *pName;

    if( !pShaderPara )
    {
        TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
        return;
    }

    mShaderParams = pShaderPara;

    //update auto uniform constant index
    count = mShaderParams->getAutoConstCount();
    for( i=0; i<count; i++)
    {
        pName = mShaderParams->getAutoConstName( i );
        mShaderParams->updateAutoConstIndex(pName, getUnifLocFromShader(pName));
    }

    //update attribution constant
    count = mShaderParams->getAttrConstCount();
    for( i=0; i<count; i++)
    {
        pName = mShaderParams->getAttrConstName( i );
        mShaderParams->updateAttrConstIndex(pName, getAttrLocFromShader(pName));
    }

    //update custom uniform constant index
    count = mShaderParams->getCustIntCount();
    for( i=0; i<count; i++)
    {
        pName = mShaderParams->getCustIntConstName( i );
        mShaderParams->updateCustIntUniformIndex(pName, getUnifLocFromShader(pName));
    }

    count = mShaderParams->getCustRealCount();
    for( i=0; i<count; i++)
    {
        pName = mShaderParams->getCustRealConstName( i );
        mShaderParams->updateCustRealUniformIndex( pName, getUnifLocFromShader(pName));
    }

    return;
}

/* -1->no constant exist */
int ShaderProgram::getAttrLocation(AttrConstantType type)
{
    return mShaderParams->getAttrConstIndex(type);
}

ShaderProgramParams* ShaderProgram::getShaderParameters()
{
    return mShaderParams;
}


Uint ShaderProgram::getShaderProgramID()
{
    return mShaderProgramID;
}


Uint ShaderProgram::loadShaderSource(const char *vertshader, const char *fragshader )
{
    Uint prog = 0;
    char*  vertSource;
    char*  fragSource;
    GLint  vertSourceLen;
    GLint  fragSourceLen;
    Uint vertShader;
    Uint fragShader;
    
    // Load the shader files
    vertSource    = loadFile(vertshader);
    fragSource    = loadFile(fragshader);
    if (!vertSource || !fragSource) goto done;
    vertSourceLen = (GLint)strlen(vertSource);
    fragSourceLen = (GLint)strlen(fragSource);
    
    // Create the program
    prog = glCreateProgram();
    if( !prog )
    {
        TOY3D_PRINT("glCreateProgram Failed.", __FILE__, __LINE__ );
        return 0;
    }
    
    // Create the GL shader objects
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Load shader sources into GL and compile
    glShaderSource(vertShader, 1, (const char**)&vertSource, &vertSourceLen);
    glCompileShader(vertShader);
    getShaderDebugInfo(vertShader, GL_COMPILE_STATUS, "Vert Compile");

    glShaderSource(fragShader, 1, (const char**)&fragSource, &fragSourceLen);
    glCompileShader(fragShader);
    getShaderDebugInfo(fragShader, GL_COMPILE_STATUS, "Frag Compile");
    
    // Attach the shaders to the program
    glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);
    
    // Delete the shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    // Link and validate the shader program
    glLinkProgram(prog);
    getShaderDebugInfo(prog, GL_LINK_STATUS, "Program Link");

    glValidateProgram(prog);
    getShaderDebugInfo(prog, GL_VALIDATE_STATUS, "Program Validate");
    
done:
    
    free(fragSource);
    free(vertSource);

    mShaderProgramID = prog;

    return prog;
}

Uint ShaderProgram::loadShaderBinary(const char* vertBinaryFile, Uint vertBFSize,
                                     const char* fragBinaryFile, Uint fragBFSize)
{
    Uint prog;
    Uint vertShader;
    Uint fragShader;
    
    // Create the program
    prog = glCreateProgram();
    
    // Create the GL shader objects
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Load the binary data into the shader objects
    glShaderBinary(1, &vertShader, BINARY_CODE_FOR_NV, vertBinaryFile, vertBFSize);
    glShaderBinary(1, &fragShader, BINARY_CODE_FOR_NV, fragBinaryFile, fragBFSize);
    
    // Attach the shaders to the program
    glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);

    // Delete the shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    // Link the shader program
    glLinkProgram(prog);
    getShaderDebugInfo(prog, GL_LINK_STATUS, "Program Link");
   
    mShaderProgramID = prog;

    return prog;
}

void ShaderProgram::getShaderDebugInfo(Uint obj, GLenum status, const char* op)
{
    int success;
    // log output.
    int len;
    char *str = NULL;
    if (status == GL_COMPILE_STATUS) {
        glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &len);
        if (len > 0) {
            str = (char *)malloc(len * sizeof(char));
            glGetShaderInfoLog(obj, len, NULL, str);
        }
    } else { // LINK
        glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &len);
        if (len > 0) {
            str = (char *)malloc(len * sizeof(char));
            glGetProgramInfoLog(obj, len, NULL, str);
        }
    }
    if (str != NULL && *str != '\0')
    {
        printf("--- %s log ---\n", op);
        printf("%s.\n", str);
    }
    if(str)
    {
        free(str);
    }
    
    // check the compile / link status.
    if (status == GL_COMPILE_STATUS)
    {
        glGetShaderiv(obj, status, &success);
        if (!success)
        {
            glGetShaderiv(obj, GL_SHADER_SOURCE_LENGTH, &len);
            if (len > 0)
            {
                str = (char *)malloc(len * sizeof(char));
                glGetShaderSource(obj, len, NULL, str);
                if (str != NULL && *str != '\0')
                {
                    printf("--- %s code ---\n", op);
                    printf("%s.\n", str);
                }
                free(str);
            }
        }
    }
    else
    {// LINK
        glGetProgramiv(obj, status, &success);
    }

    if (!success)
    {
        printf("--- %s failed ---\n", op);
        //exit(-1);
        return;
    }

    return;
}

char* ShaderProgram::loadFile(const char *file)
{
    //char path[MAX_PATH_SIZE];
    struct stat st;
    char *data;
    FILE *f;

    /*
    strcpy(path, RES_FILE_CONTENT );
    strncat(path, file, 1000);
    f = fopen(path, "rb");

    if (!f) {
        strcpy(path, RES_FILE_CONTENT2);
        strncat(path, file, 1000);
        f = fopen(path, "rb");
    }
    */
//    strncpy(path, file, MAX_PATH_SIZE);
    f = fopen(file, "rb");
    if (!f) {
        printf("Unable to open shader: %s.\n", file);
        return 0;
    }

    if(stat(file, &st)) {
        printf("Unable to stat shader: %s.\n", file);
        fclose(f);
        return 0;
    }

    data = (char *)malloc(st.st_size + 1);
    if(!data) {
        printf("Unable to allocate memory for shader: %s\n", file);
        fclose(f);
        return 0;
    }
    if(fread(data, 1, st.st_size, f) != st.st_size) {
        printf("Unable to read shader: %s\n", file);

        fclose(f);
        return 0;
    }
    data[st.st_size] = 0;
    fclose(f);

    return data;
}


TOY3D_END_NAMESPACE

