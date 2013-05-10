
#include "myapp.h"
#include "user_data.h"

TOY3D_BEGIN_NAMESPACE


#define VERTEX_COUNT_RECT 6
#define VERTEX_COUNT_TRI  3


Real vertices_rect_1[VERTEX_COUNT_RECT * 3] = {
    -6.0f, -2.0f, 0.0f,
    -2.0f,  -2.0f, 0.0f,
    -6.0f,  2.0f, 0.0f,
        
    -2.0f,  2.0f, 0.0f,
    -2.0f, -2.0f, 0.0f,
    -6.0f, 2.0f, 0.0f
};


Real vertices_rect_2[VERTEX_COUNT_RECT * 3] = {
    0.0f, -2.0f, 0.0f,
    4.0f,  -2.0f, 0.0f,
    0.0f,  2.0f, 0.0f,
        
    4.0f,  2.0f, 0.0f,
    4.0f, -2.0f, 0.0f,
    0.0f, 2.0f, 0.0f
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
    mMeshTexture1 = NULL;
    mMeshTexture2 = NULL;
    mMeshTriangle = NULL;

    mEntityTriangle = NULL;
    mEntityTexture1 = NULL;
    mEntityTexture2 = NULL;
}

MyApp::~MyApp()
{
    ShaderProgramManager::getInstance()->destroyAllShaderProgramParams();
    ShaderProgramManager::getInstance()->destroyAllShaderPrograms();

    MeshManager::getInstance()->destroyAllMeshes();

    MaterialManager::getInstance()->destroyAllMaterials();

    mRTex1->removeListener(this);
    mRTex2->removeListener(this);

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
    Texture *tex1 = TextureManager::getInstance()->createTexture(NULL, width, height, bpp);
    if(!tex1)
    {
        printf("Failed to create texture1.\n");
        return false;
    }
    mRTex1 = mWorld->createRenderTexture(tex1);
    if(!mRTex1)
    {
        printf("Failed to create RenderTexture.\n");
        return false;
    }
    mRTex1->addViewport(mCamera, 0, 0, width, height);



    Texture *tex2 = TextureManager::getInstance()->createTexture(NULL, width, height, bpp);
    if(!tex2)
    {
        printf("Failed to create texture2.\n");
        return false;
    }
    mRTex2 = mWorld->createRenderTexture(tex2);
    if(!mRTex2)
    {
        printf("Failed to create RenderTexture.\n");
        return false;
    }
    mRTex2->addViewport(mCamera, 0, 0, width, height);




    mWin = mWorld->createRenderWindow ();
    mWin->addViewport(mCamera, 0, 0, width, height);


    mMeshTexture1 = MeshManager::getInstance()->createMesh();
    mMeshTexture1->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mMeshTexture1->setVertices (vertices_rect_1, VERTEX_COUNT_RECT);
    mMeshTexture1->setUVs( uvs, VERTEX_COUNT_RECT);


    mMeshTexture2 = MeshManager::getInstance()->createMesh();
    mMeshTexture2->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mMeshTexture2->setVertices (vertices_rect_2, VERTEX_COUNT_RECT);
    mMeshTexture2->setUVs( uvs, VERTEX_COUNT_RECT);



    mMeshTriangle = MeshManager::getInstance()->createMesh();
    mMeshTriangle->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mMeshTriangle->setVertices (vertices_triangle, VERTEX_COUNT_TRI);

    Material *mat = MaterialManager::getInstance()->createMaterial();
    mat->setShaderProgram (mShaderTex);
//    printf("Working Shader : Rendering Texture.\n\n");

    mEntityTriangle = mWorld->createEntity();
    mEntityTriangle->setMesh(mMeshTriangle);
    mEntityTriangle->setMaterial(mat);

    mat = NULL;
    mat = MaterialManager::getInstance()->createMaterial();
    mat->setShaderProgram (mShaderWin);
 
    mEntityTexture1 = mWorld->createEntity();
    mEntityTexture1->setMesh(mMeshTexture1);
    mEntityTexture1->setMaterial(mat);

    mEntityTexture2 = mWorld->createEntity();
    mEntityTexture2->setMesh(mMeshTexture2);
    mEntityTexture2->setMaterial(mat);


/*
    //Entity
    mEntity = mWorld->createEntity();
    mEntity->setMesh(mMesh_tex);
    mEntity->setMaterial(mat);
*/



    mRTex1->addListener(this);
    mRTex2->addListener(this);

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
    Real nearz  = 1.0f;
    Real farz   = 1000.0f;
    Viewport *vp = NULL;

    mWorld->setSize(w, h);

    aspect = 1.0 * w / h;
    fovy = 60;
    mCamera->perspective (fovy, aspect, nearz, farz);
    mCamera->lookAt (0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    vp = mWin->getViewport(0);
    vp->setWidth((Uint)w);
    vp->setHeight((Uint)h);

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
    mEntityTriangle->setVisible (true);
    mEntityTexture1->setVisible (false);
    mEntityTexture2->setVisible (false);
    printf("Working Shader : Rendering Texture.\n\n");
    return;
}

void MyApp::postRenderTargetUpdate()
{
    mWorld->setBackColor(0, 0, 1, 1);
    mEntityTriangle->setVisible (false);
    mEntityTexture1->setVisible (true);
    mEntityTexture2->setVisible (true);
    printf("Working Shader : Rendering Window.\n\n");
    return;
}


TOY3D_END_NAMESPACE
