#ifndef _MY_APP_H
#define _MY_APP_H



#include <toy3d/Toy3DFrameListener.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DEntity.h>
#include <toy3d/Toy3DRenderWindow.h>
#include <toy3d/Toy3DRenderTexture.h>

#include <toy3d/Toy3DShaderProgramParams.h>
#include <toy3d/Toy3DShaderProgramManager.h>
#include <toy3d/Toy3DMeshManager.h>
#include <toy3d/Toy3DMaterialManager.h>

TOY3D_BEGIN_NAMESPACE

class MyApp : public FrameListener
{
#define LOOP_LIMIT 5

public:
    MyApp();
    ~MyApp();

    Bool createScene();
    void startRendering();
    void changeWindowSize(int w, int h);

    bool frameStarted();
    bool frameEnded ();

    World *mWorld;
    Camera *mCamera;
    RenderWindow *mWin;
    Entity *mRect;

private:
    Bool mIsVisible;
    Uint mLoopCtrl;
};


TOY3D_END_NAMESPACE


#endif