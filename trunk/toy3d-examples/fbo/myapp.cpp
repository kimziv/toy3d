
#include "myapp.h"
#include "user_data.h"

TOY3D_BEGIN_NAMESPACE


#define VERTEX_COUNT_RECT 6
#define VERTEX_COUNT_TRI  3


Real vertices_rect[VERTEX_COUNT_RECT * 3] = {
    -2.0f, -2.0f, 0.0f,
    2.0f,  -2.0f, 0.0f,
    -2.0f,  2.0f, 0.0f,
        
    2.0f,  2.0f, 0.0f,
    2.0f, -2.0f, 0.0f,
    -2.0f, 2.0f, 0.0f
};

Real vertices_triangle[VERTEX_COUNT_TRI * 3] = {
    0.0f, 1.0f, 0.0f,
    -1.0f,  -1.0f, 0.0f,
    1.0f, -1.0f,  0.0f,
};

Real uvs[VERTEX_COUNT_RECT * 2] = {
    0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f,
    1.0f,1.0f, 1.0f,0.0f, 0.0f,1.0f
};

Real angle_y = 0.0f;


MyApp::MyApp()
{
    mWorld  = NULL;
    mEntity = NULL;
    mCamera = NULL;
    mShaderWin = NULL;
    mShaderTex = NULL;
    mMesh_win = NULL;
    mMesh_tex = NULL;
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

    initShader(mShaderTex, mShaderWin);


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


    mMesh_win = MeshManager::getInstance()->createMesh();
    mMesh_win->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mMesh_win->setVertices (vertices_rect, VERTEX_COUNT_RECT);
    mMesh_win->setUVs( uvs, VERTEX_COUNT_RECT);

    mMesh_tex = MeshManager::getInstance()->createMesh();
    mMesh_tex->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mMesh_tex->setVertices (vertices_triangle, VERTEX_COUNT_TRI);

    Material *mat = MaterialManager::getInstance()->createMaterial();
    mat->setShaderProgram (mShaderTex);
    printf("Working Shader : Rendering Texture.\n\n");

    //Entity
    mEntity = mWorld->createEntity();
    mEntity->setMesh(mMesh_tex);
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

void MyApp::initShader(ShaderProgram *pShaderTex, ShaderProgram *pShaderWin)
{
    int   texUnit = 0;
    ShaderProgramParams *params = NULL;

    pShaderTex->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE_TEX);
    params = ShaderProgramManager::getInstance()->createShaderProgramParams();
    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");
    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX, "vPosition");

    pShaderTex->bindShaderParameters(params);


    pShaderWin->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE_WIN);
    params = ShaderProgramManager::getInstance()->createShaderProgramParams();
    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");
    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX, "vPosition");
    params->setNamedAttrConstant (TOY3D_ATTR_UV, "vTexture");
    //shader custom constant
    params->setNamedCustUniformConstant(TOY3D_CUST_SAMPLER2D, "sampler2d", texUnit);

    pShaderWin->bindShaderParameters(params);

    return;
}

void MyApp::preRenderTargetUpdate()
{
    mWorld->setBackColor(1, 0, 0, 0);
    mEntity->setMesh(mMesh_tex);
    mEntity->getMaterial()->setShaderProgram(mShaderTex);
    printf("Working Shader : Rendering Texture.\n\n");
    return;
}

void MyApp::postRenderTargetUpdate()
{
    mWorld->setBackColor(0, 0, 1, 1);
    mEntity->setMesh(mMesh_win);
    mEntity->getMaterial()->setShaderProgram(mShaderWin);
    printf("Working Shader : Rendering Window.\n\n");
    return;
}


TOY3D_END_NAMESPACE