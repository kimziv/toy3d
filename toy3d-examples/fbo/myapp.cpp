
#include "myapp.h"
#include "user_data.h"

TOY3D_BEGIN_NAMESPACE


#define VERTEX_COUNT  6    


Real vertices[VERTEX_COUNT * 3] = {
    -1.0f, -1.0f, 0.0f,
    1.0f,  -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
        
    1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f
};

Real angle_y = 0.0f;


MyApp::MyApp()
{
    mWorld  = NULL;
    mEntity = NULL;
    mCamera = NULL;
    mShaderWin = NULL;
    mShaderTex = NULL;
}

MyApp::~MyApp()
{
    ShaderProgramManager::getInstance()->destroyAllShaderProgramParams();
    ShaderProgramManager::getInstance()->destroyAllShaderPrograms();

    MeshManager::getInstance()->destroyAllMeshes();

    MaterialManager::getInstance()->destroyAllMaterials();

    mRTex->removeListener(this);

    mWorld->destroyAllEntities();
}

Bool MyApp::createScene()
{
    int   width = WINDOW_W, height = WINDOW_H;
    int   bpp = BPP_4;

    mWorld = new World ();
    mWorld->setSize(width, height);
    mWorld->setBackColor (1.0, 1.0, 1.0, 1.0);
    
    mCamera = mWorld->createCamera ("camera1");

    //creat the shader for rendering window
    mShaderWin = ShaderProgramManager::getInstance()->createShaderProgram();
    //creat the shader for rendering texture
    mShaderTex = ShaderProgramManager::getInstance()->createShaderProgram();

    initShader(mShaderWin, mShaderTex);


    //create a texture, a RenderTexture
    Texture *tex = TextureManager::getInstance()->createTexture(NULL, width, height, bpp);
    if(!tex)
    {
        printf("Failed to create texture.\n");
        return false;
    }
    mRTex = mWorld->createRenderTexture(tex);
    if(!mRTex)
    {
        printf("Failed to create RenderTexture.\n");
        return false;
    }
    mRTex->addViewport(mCamera, 0, 0, width, height);

    mWin = mWorld->createRenderWindow ();
    mWin->addViewport(mCamera, 0, 0, width, height);


    Mesh* mesh = MeshManager::getInstance()->createMesh();
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mesh->setVertices (vertices, VERTEX_COUNT);
    
    Material *mat = MaterialManager::getInstance()->createMaterial();
    mat->setShaderProgram (mShaderTex);
    printf("Working Shader : Rendering Texture.\n\n");

    //Entity
    mEntity = mWorld->createEntity();
    mEntity->setMesh(mesh);
    mEntity->setMaterial(mat);


    mRTex->addListener(this);

    return TRUE;
}

void MyApp::startRendering()
{
    mWorld->renderOneFrame();
    return;
}

void MyApp::changeWindowSize(int w, int h)
{
    Real aspect, fovy;
    Real nearz  = 1.0f;//5.0f;
    Real farz   = 1000.0f;//60.0f;
    
    mWorld->setSize(w, h);
    
    aspect = 1.0 * w / h;
    fovy = 60;
    mCamera->perspective (fovy, aspect, nearz, farz);
    mCamera->lookAt (0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    
    return;
}

void MyApp::initShader(ShaderProgram *pShader1, ShaderProgram *pShader2)
{
    int   texUnit = 0;
    ShaderProgramParams *params = NULL;

    pShader1->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE_WIN);
    params = ShaderProgramManager::getInstance()->createShaderProgramParams();
    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");
    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX, "vPosition");

    pShader1->bindShaderParameters(params);


    pShader2->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE_WIN);
    params = ShaderProgramManager::getInstance()->createShaderProgramParams();
    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");
    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX, "vPosition");
    //shader custom constant
    params->setNamedCustUniformConstant(TOY3D_CUST_SAMPLER2D, "sampler2d", texUnit);

    pShader2->bindShaderParameters(params);

    return;
}

void MyApp::preRenderTargetUpdate()
{
    mEntity->getMaterial()->setShaderProgram(mShaderTex);
    printf("Working Shader : Rendering Texture.\n\n");
    return;
}

void MyApp::postRenderTargetUpdate()
{
    mEntity->getMaterial()->setShaderProgram(mShaderWin);
    printf("Working Shader : Rendering Window.\n\n");
    return;
}


TOY3D_END_NAMESPACE