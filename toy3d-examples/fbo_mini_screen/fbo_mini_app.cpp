
#include "fbo_mini_app.h"
#include "fbo_mini_app_data.h"

TOY3D_BEGIN_NAMESPACE


#define VERTEX_COUNT_RECT 6
#define VERTEX_COUNT_TRI  3



Real vertices_rect[VERTEX_COUNT_RECT * 3] = {
    1.5f, -3.0f, 0.0f,
    3.5f, -3.0f, 0.0f,
    1.5f, -1.0f, 0.0f,
        
    3.5f, -1.0f, 0.0f,
    3.5f, -3.0f, 0.0f,
    1.5f, -1.0f, 0.0f
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
    mEntityMini = NULL;
    mCamera = NULL;
    mShaderRender = NULL;
    mShaderRenderWithTex = NULL;
    mMesh_for_tex = NULL;
    mMesh_triangle = NULL;

    mWinMain = NULL;
    mRTex = NULL;
    mWin = NULL;

    mEntityMain = NULL;
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
    Material *mat_render_tex, *mat_render;

    mWorld = new World ();
    mWorld->setSize(width, height);
    mWorld->setBackColor (1.0, 1.0, 1.0, 1.0);

    mCamera = mWorld->createCamera ("camera1");

    //creat the shader for rendering window
    mShaderRender = ShaderProgramManager::getInstance()->createShaderProgram();
    //creat the shader for rendering texture
    mShaderRenderWithTex = ShaderProgramManager::getInstance()->createShaderProgram();
    initShader(mShaderRender, mShaderRenderWithTex);

    //create tender target
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

    //add render target listener
    mRTex->addListener(this);


    //mesh
    mMesh_for_tex = MeshManager::getInstance()->createMesh();
    mMesh_for_tex->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mMesh_for_tex->setVertices (vertices_rect, VERTEX_COUNT_RECT);
    mMesh_for_tex->setUVs( uvs, VERTEX_COUNT_RECT);

    mMesh_triangle = MeshManager::getInstance()->createMesh();
    mMesh_triangle->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mMesh_triangle->setVertices (vertices_triangle, VERTEX_COUNT_TRI);


    //material
    mat_render = MaterialManager::getInstance()->createMaterial();
    mat_render->setShaderProgram (mShaderRender);

    mat_render_tex = MaterialManager::getInstance()->createMaterial();
    mat_render_tex->setShaderProgram (mShaderRenderWithTex);


    //Entity
    mEntityMain = mWorld->createEntity();
    mEntityMain->setMesh(mMesh_triangle);
    mEntityMain->setMaterial(mat_render);
    mEntityMain->setVisible(TRUE);

    mEntityMini = mWorld->createEntity();
    mEntityMini->setMesh(mMesh_for_tex);
    mEntityMini->setMaterial(mat_render_tex);
    mEntityMini->setVisible(FALSE);

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
    Viewport *vp = NULL;
    
    mWorld->setSize(w, h);
    
    aspect = 1.0 * w / h;
    fovy = 60;
    mCamera->perspective (fovy, aspect, nearz, farz);
    mCamera->lookAt (0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);


    vp = mWin->getViewport(0);
    vp->setWidth( w );
    vp->setHeight( h );

    return;
}

void MyApp::initShader(ShaderProgram *pShaderRender, ShaderProgram *pShaderRenderWithTex)
{
    int   texUnit = 0;
    ShaderProgramParams *params = NULL;

    pShaderRender->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE_RENDER);
    params = ShaderProgramManager::getInstance()->createShaderProgramParams();
    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");
    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX, "vPosition");

    pShaderRender->bindShaderParameters(params);


    pShaderRenderWithTex->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE_RENDER_WITH_TEX);
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

    pShaderRenderWithTex->bindShaderParameters(params);

    return;
}

void MyApp::preRenderTargetUpdate()
{
    mWorld->setBackColor(1, 0, 0, 1);
    mEntityMini->setVisible(FALSE);

    return;
}

void MyApp::postRenderTargetUpdate()
{
    mWorld->setBackColor(1, 1, 1, 1);
    mEntityMini->setVisible(TRUE);

    return;
}


TOY3D_END_NAMESPACE