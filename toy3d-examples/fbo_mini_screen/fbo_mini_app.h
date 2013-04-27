#ifndef _MY_APP_H
#define _MY_APP_H



#include <toy3d/Toy3DRenderTargetListener.h>

#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DEntity.h>
#include <toy3d/Toy3DRenderWindow.h>
#include <toy3d/Toy3DRenderTexture.h>
#include <toy3d/Toy3DRenderTarget.h>

#include <toy3d/Toy3DShaderProgramParams.h>
#include <toy3d/Toy3DShaderProgramManager.h>
#include <toy3d/Toy3DMeshManager.h>
#include <toy3d/Toy3DMaterialManager.h>
#include <toy3d/Toy3DTexture.h>
#include <toy3d/Toy3DTextureManager.h>
#include <toy3d/Toy3DViewport.h>


TOY3D_BEGIN_NAMESPACE



class MyApp : public RenderTargetListener
{
#define LOOP_LIMIT 5

public:
    MyApp();
    ~MyApp();

    Bool createScene();
    void startRendering();
    void changeWindowSize(int w, int h);

    void preRenderTargetUpdate();
    void postRenderTargetUpdate();

    World *mWorld;
    Camera *mCamera;
    Entity *mEntityMini;
    Entity *mEntityMain;


private:
    ShaderProgram *mShaderRender, *mShaderRenderWithTex;
    RenderTexture *mRTex;
    RenderWindow  *mWin;
    RenderWindow  *mWinMain;

    Mesh *mMesh_triangle;
    Mesh *mMesh_for_tex;
    Mesh *mMesh_main;

    void initShader(ShaderProgram *pShaderRender, ShaderProgram *pShaderRenderWithTex);
};


TOY3D_END_NAMESPACE


#endif