
#include "Toy3DShaderProgram.h"
#include "Toy3DShaderProgramParams.h"
#include <sys/stat.h>

TOY3D_BEGIN_NAMESPACE

ShaderProgram::ShaderProgram()
{
    mShaderParams = 0;
}

ShaderProgram::~ShaderProgram()
{
    if( mShaderParams )
        FREEANDNULL(mShaderParams);
}

Uint ShaderProgram::loadShaderSource(Uchar *vertshader, Uchar *frashader )
{
    mShaderProgramID = MvGl2DemoLoadShaderSources(
        (const char *)vertshader, (const char *)frashader, GL_FALSE);
    if ( 0 == mShaderProgramID )
    {
        PRINT("loadShaderSource: Failed to load shader.\n ");
        return 0;
    }

    return mShaderProgramID;
}

Uint ShaderProgram::loadShaerBinary(Uchar *bvertshader,
                                    Uint vertLength, Uchar *bfrashader, Uint fragLength )
{
    mShaderProgramID = MvGl2DemoLoadShaderBinaries(
        (const char *)bfrashader, vertLength, (const char *)bfrashader, fragLength, GL_FALSE);
    if ( 0 == mShaderProgramID )
    {
        PRINT("loadShaerBinary: Failed to load shader.\n ");
        return 0;
    }

    return mShaderProgramID;
}

void ShaderProgram::bindShaderParameters(ShaderProgramParams* pShaderPara)
{
    Uint count, i;
    Uchar *pName;

    if( !pShaderPara )
    {
        PRINT("NULL POINTER.FILE: %s, LINE: %d.\n", __FILE__, __LINE__ );
        return;
    }

    mShaderParams = pShaderPara;
    count = mShaderParams->getEntryCount();
    for( i=0; i<count; i++)
    {
        pName = mShaderParams->getParamName( i );
        mShaderParams->updateAutoConstIndex( pName,
            glGetUniformLocation(mShaderProgramID, (const char *)pName) );
    }

    return;
}

ShaderProgramParams* ShaderProgram::getShaderParameters()
{
    return mShaderParams;
}


Uint ShaderProgram::getShaderProgramID()
{
    return mShaderProgramID;
}

Uint ShaderProgram::MvGl2DemoLoadShaderSources(
                                  const char* vertFile,
                                  const char* fragFile,
                                  GLboolean debugging)
{
    Uint prog = 0;
    char*  vertSource;
    char*  fragSource;
    GLint  vertSourceLen;
    GLint  fragSourceLen;
    Uint vertShader;
    Uint fragShader;
    
    // Load the shader files
    vertSource    = MvGl2DemoLoadFile(vertFile);
    fragSource    = MvGl2DemoLoadFile(fragFile);
    if (!vertSource || !fragSource) goto done;
    vertSourceLen = (GLint)strlen(vertSource);
    fragSourceLen = (GLint)strlen(fragSource);
    
    // Create the program
    prog = glCreateProgram();
    
    // Create the GL shader objects
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Load shader sources into GL and compile
    glShaderSource(vertShader, 1, (const char**)&vertSource, &vertSourceLen);
    glCompileShader(vertShader);
    if (debugging)
        MvGl2DemoShaderDebug(vertShader, GL_COMPILE_STATUS, "Vert Compile");
    glShaderSource(fragShader, 1, (const char**)&fragSource, &fragSourceLen);
    glCompileShader(fragShader);
    if (debugging)
        MvGl2DemoShaderDebug(fragShader, GL_COMPILE_STATUS, "Frag Compile");
    
    // Attach the shaders to the program
    glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);
    
    // Delete the shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    // Link and validate the shader program
    glLinkProgram(prog);
    if (debugging)
        MvGl2DemoShaderDebug(prog, GL_LINK_STATUS, "Program Link");
    glValidateProgram(prog);
    if (debugging)
        MvGl2DemoShaderDebug(prog, GL_VALIDATE_STATUS, "Program Validate");
    
done:
    
    free(fragSource);
    free(vertSource);
    return prog;
}

Uint ShaderProgram::MvGl2DemoLoadShaderBinaries(
                                   const char* vertBin, Uint vertBinSize,
                                   const char* fragBin, Uint fragBinSize,
                                   GLboolean debugging)
{
    // Binary shaders not supportable for non-ES OpenGL
#ifdef GL_ES_VERSION_2_0
    
    Uint prog;
    Uint vertShader;
    Uint fragShader;
    
    // Create the program
    prog = glCreateProgram();
    
    // Create the GL shader objects
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Load the binary data into the shader objects
    glShaderBinary(1, &vertShader,
        GL_NVIDIA_PLATFORM_BINARY_NV, vertBin, vertBinSize);
    glShaderBinary(1, &fragShader,
        GL_NVIDIA_PLATFORM_BINARY_NV, fragBin, fragBinSize);
    
    // Attach the shaders to the program
    glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);
    
#if 0
    // Delete the shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
#endif
    
    // Link the shader program
    glLinkProgram(prog);
    if (debugging)
        MvGl2DemoShaderDebug(prog, GL_LINK_STATUS, "Program Link");
    
    return prog;
#else  // GL_ES_VERSION_2_0
    return 0;
#endif // GL_ES_VERSION_2_0
}

void ShaderProgram::MvGl2DemoLogMessage(const char* message, ...)
{
    va_list pArgList;
    char    szBuffer[512];
    
    va_start(pArgList, message);
    _vsnprintf(szBuffer, sizeof(szBuffer) / sizeof(char), message, pArgList);
    va_end(pArgList);
    fprintf (stderr, szBuffer);
    
    return;
}

void ShaderProgram::MvGl2DemoShaderDebug(Uint obj, GLenum status, const char* op)
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
    if (str != NULL && *str != '\0') {
        MvGl2DemoLogMessage("--- %s log ---\n", op);
        MvGl2DemoLogMessage(str);
    }
    if (str) { free(str); }
    
    // check the compile / link status.
    if (status == GL_COMPILE_STATUS) {
        glGetShaderiv(obj, status, &success);
        if (!success) {
            glGetShaderiv(obj, GL_SHADER_SOURCE_LENGTH, &len);
            if (len > 0) {
                str = (char *)malloc(len * sizeof(char));
                glGetShaderSource(obj, len, NULL, str);
                if (str != NULL && *str != '\0') {
                    MvGl2DemoLogMessage("--- %s code ---\n", op);
                    MvGl2DemoLogMessage(str);
                }
                free(str);
            }
        }
    } else { // LINK
        glGetProgramiv(obj, status, &success);
    }
    
    if (!success)
    {
        MvGl2DemoLogMessage("--- %s failed ---\n", op);
        exit(-1);
    }
}

char* ShaderProgram::MvGl2DemoLoadFile(const char *file)
{
    char path[1024];
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
    strncpy(path, file, 1000);
    f = fopen(path, "rb");
    if (!f) {
        MvGl2DemoLogMessage("Unable to open shader: %s.\n", file);
        return 0;
    }

    if(stat(path, &st)) {
        MvGl2DemoLogMessage("Unable to stat shader: %s.\n", file);
        fclose(f);
        return 0;
    }

    data = (char *)malloc(st.st_size + 1);
    if(!data) {
        MvGl2DemoLogMessage("Unable to allocate memory for shader: %s\n", file);
        fclose(f);
        return 0;
    }
    if(fread(data, 1, st.st_size, f) != st.st_size) {
        MvGl2DemoLogMessage("Unable to read shader: %s\n", file);

        fclose(f);
        return 0;
    }
    data[st.st_size] = 0;
    fclose(f);

    return data;
}


TOY3D_END_NAMESPACE

