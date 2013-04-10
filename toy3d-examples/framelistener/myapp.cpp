
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
    mRect   = NULL;
    mCamera = NULL;
    mWin    = NULL;

    mIsVisible = TRUE;
    mLoopCtrl = 0;
}

MyApp::~MyApp()
{
    ShaderProgramManager::getInstance()->destroyAllShaderProgramParams();
    ShaderProgramManager::getInstance()->destroyAllShaderPrograms();

    MeshManager::getInstance()->destroyAllMeshes();

    MaterialManager::getInstance()->destroyAllMaterials();

    mWorld->removeFrameListener(this);

    mWorld->destroyAllEntities();
}

Bool MyApp::createScene()
{
    int   width = WINDOW_W, height = WINDOW_H;
    const Real nearz  = 1.0f;//5.0f;
    const Real farz   = 1000.0f;//60.0f;
    int   texUnit = 0;
    
    mWorld = new World ();
    mWorld->setSize(WINDOW_W, WINDOW_H);
    mWorld->setBackColor (1.0, 1.0, 1.0, 1.0);
    
    mCamera = mWorld->createCamera ("camera1");
    
    mWin = mWorld->createRenderWindow ();
    mWin->addViewport (mCamera, 0, 0, width, height);
    
    RenderWindow *win = mWorld->createRenderWindow ();
    win->addViewport (mCamera, 0, 0, WINDOW_W, WINDOW_H);
    
    ShaderProgram *shaderProgram = ShaderProgramManager::getInstance()->createShaderProgram();
    shaderProgram->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE);
    
    ShaderProgramParams *params = ShaderProgramManager::getInstance()->createShaderProgramParams();
    
    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");
    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX, "vPosition");
    //shader custom constant
    params->setNamedCustUniformConstant(TOY3D_CUST_SAMPLER2D, "sampler2d", texUnit);
    
    shaderProgram->bindShaderParameters(params);
    
    
    Mesh* mesh = MeshManager::getInstance()->createMesh();
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mesh->setVertices (vertices, VERTEX_COUNT);
    
    Material *mat = MaterialManager::getInstance()->createMaterial();
    mat->setShaderProgram (shaderProgram);
    
    //Entity
    mRect = mWorld->createEntity();
    mRect->setMesh(mesh);
    mRect->setMaterial(mat);

    mWorld->addFrameListener(this);
    
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

bool MyApp::frameStarted()
{
    mLoopCtrl++;
    if(LOOP_LIMIT==mLoopCtrl)
    {
        mIsVisible = !mIsVisible;
        mRect->setVisible(mIsVisible);
        mLoopCtrl = 0;
    }

    return TRUE;
}

bool MyApp::frameEnded()
{
    return TRUE;
}

TOY3D_END_NAMESPACE
