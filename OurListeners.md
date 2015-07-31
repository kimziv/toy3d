# 遗留问题 #

多个 target listener 如何与 myapp 关联？
target listener 里的 pre/post 接口访问 entity

framelistener 和 rendertarget listener 如何释放？


# 观察者模式 #

C语言中的回调函数




# Frame Listener #

## 需求 ##

给用户提供机会在开始每一帧之前和之后做一些事情，比如设置 set entity visible

## 设计与实现 ##

实现方法：
  * 设计一个基类作为接口
  * 定义 FrameListener 容器，保存所有注册了的帧监听
  * 在 renderOenFrame 里绘制每帧都调用基类的函数
  * 用户使用时，先基于基类实现自己的 frame listener，然后注册到容器中


基类 FrameListener 的设计：

```

class FrameListener
{
public:
    virtual bool frameStarted () {return TRUE};
    virtual bool frameEnded() {return TRUE};

};

```

World 中定义 FrameListener 容器

```

class World
{ 
    TPArray mFrameListeners;
}

World::World()
{
    mFrameListeners.create();
}


```


renderOneFrame 中的处理：

```



Bool World::renderOneFrame ()
{

    if(fireFrameStarted())   //user implemnet it to do something
        
 
    updateAllRenderTargets();

    return fireFrameEnded();     //user implement it to do something
}

bool World::fireFrameStarted ()
{
    for (int i = 0; i < mFrameListeners.getLength(); i++) {
        FrameListerer* fl = mFrameListeners.geElement(i);
        if(fl->frameStarted())
            return FALSE;
    }

    return TRUE;
}


bool World::fireFrameEnded ()
{
    for (int i = 0; i < mFrameListeners.getLength(); i++) {
        FrameListerer* fl = mFrameListeners.geElement(i);
        if(fl->frameEnded())
            return FALSE;
    }

    return TRUE;
}


    
```


注册和删除 frame listener


```

void World::addFrameListener:(FrameListener* newListener)
{
    mFrameListeners.append (newListener);
}


void World::removeFrameListener:(FrameListener* oldListener)
{
    mFrameListeners.remove (oldListener);
}


```

## 使用样例 ##


```

class myApp:public FrameListener
{
    myApp()
    ~myApp();

    void createScene();
    void startRendering();
    void changeWindowSize (int w, int h);

    Bool frameStarted();
    Bool frameEnded ();

    World *mWorld;
    Camera *mCamera;
    RenderWindow *mWin;
    Entity *mRect;
    
    
}


void myApp::App ()
{
    mWorld = NULL;
    mCamera = NULL;
    mRenderWindow = NULL;
    mRect = NULL;
    
}


void myApp::createScene ()
{
    mWorld->new World();
    mWorld->setSize(...);
    mWorld->setBackColor(...);

    mWorld->addFrameListener(this);
  
    mCamera = world->createCamera(...);

    mWin = world->createRenderWindow();
    mWin->addViewport (camera, 0,0, w, h);
   
    
    ShaderProgram ...
    mesh...
    entity...

    

    return;
    
}

void myApp::changeWindowSize (int w, int h)
{
    world->setSize(w, h);

    camera->perspective (fovy, aspect, nearz, farz);
    camera->lookAt (...）；
}

void myApp::startRenderering ()
{
    mWorld->renderOneFrame();
}

Bool myApp::frameStarted()
{
    isVisible = mRect->setVisible();
    mRect->setVisible(!isVisible);

    return true;
}

====

MyApp *myApp;

void init()
{
    myApp = new MyApp();
    ....
    
}

void render()
{
}


```

# target listener #

## 需求 ##
给用户提供机会在update每一个 target 之前和之后做一些事情，比如在多个 shader 间切换


## 设计与实现 ##

基本思路如 frame listener 类似，实现方法：
  * 设计一个基类作为接口
  * 在 RenderTarget 中定义 FrameListener 容器，保存所有注册了的帧监听
  * 在 RenderTarget 中每次 update 之前、之后都调用基类的函数
  * 用户使用时，先基于基类实现自己的 target listener，然后注册到容器中



```

class RenderTargetListener
{
public:
    virtual ~RenderTargetListener() {}
    virtual void preRenderTargetUpdate() {}
    virtual void postRenderTargetUpdate() {}
    virtual void preViewportUpdate() {}
    virtual void postViewportUpdate() {}
    virtual void viewportAdded() {}
    virtual void viewportRemoved() {}
}


class RenderTarget
{
private:
    TPtrArray mListeners;


    /* Internal function */
    virtual void firePreUpdate();
    virtual void firePostUpdate();


public:
    virtual void addListener (RenderTargetListener * listener);
    virtual void removeListener (RenderTargetListener *listener);
    virtual void removeAllListeners (void);
}



void RenderTarget::update()
{

    firePreUpdate()

    updateAllViewports();

    firePostUpdate()
}


void RenderTarget:;firePreUpdate()
{
    for (all target listeners)
        tl->preRenderTargetUpate()
}

void RenderTarget::firePostUpdate()
{
    for (all target listeners)
        tl->postRenderTargetUpate()

}


```


## 使用样例 ##

一个 listener

```
class MyApp : public RenderTargetListener
{

    void createScene();
    void preRenderTargetUpdate();
    void postRenderTargetUpdate();

    World *mWorld;
    Entity *mEntity;
    
}

void MyApp::createScene ()
{
    create world, camera, shader, entity, render window, render texture
    ...
    renderTexture->addListener(this);
}

void MyApp::preRenderTargetUpdate()
{
    entity->getMaterial->setShader(newShader);
}

void MyApp::postRenderTargetUpdate()
{
}


```

多个 listener的情况
  * 以地图为例
  * 设 2 个 render texture，一个 render window
  * 道路部分画在 render texture 1，building 部分画在 render texture2

```

class RoadUpdateListener: public RenderTargetListener
{
    void preRenderTargetUpdate();
    void postRenderTargetUpdate();

    World* mWorld;
}

void RoadUpdateListener::preRenderTargetUpdate()
{
    world->getEntity("roadXXX")->setVisible(true);

    World *mWorld;
}


void RoadUpdateListener::postRenderTargetUpdate()
{
    mWorld->getEntity("roadXXX")->setVisible(false);
    
}


class BuildingUpdateListener: public RenderTargetListener
{
    void preRenderTargetUpdate();
    void postRenderTargetUpdate();
}

class MyApp
{

    void createScene();
  
private:
    RoadUpdateListener *mRoadListener;
    BuildingUpdateListener *mBuildingListener;

}


void MyApp::createScene()
{
    Texture *roadTex =  TextureManager->create();
    Texture *buildingTex =  TextureManager->create();

    RenderTexture *roadRT = world->createRenderTexture (roadTex);
    RenderTexture *buildingRT = world->createRenderTexture (buildingTex);

    mRoadListener = new RoadUpdateListener (world);
    mBuildingListener = new BuildingUpdateListener (world);

    raodRT->addListener(mRoadListener);
    buildingRT->addListener(mBuildingListener); 
}

```

# OGRE frame listener 研究 #

## OGRE 中的 FrameListener ##

OGRE 中定义了了 FrameListener，应用在使用时重载自己的 listener

OGRE引擎FrameListener.h中定义的一个类。FrameListener定义如下：

```
    class _OgreExport FrameListener

    {       

    public:

        // 帧渲染之前的事件处理方法

        virtual bool frameStarted(const FrameEvent& evt) { return true; }

        //Called after all render targets have had their rendering commands 
            issued, but before render windows have been asked to flip their 
            buffers over
        virtual bool frameRenderingQueued(const FrameEvent& evt)

        // 帧渲染之后的事件处理方法

        virtual bool frameEnded(const FrameEvent& evt) { return true; }

        virtual ~FrameListener() {}         

    };

```

OGRE引擎在渲染过程中的每一帧之前调用frameStarted方法，而之后会调用frameEnded方法，通过这种方式，可以在渲染期间对场景物体（包括摄象机）进行移动、缩放等控制，当然也可以完成其它的处理。


```

class ExampleFrameListener : public FrameListener
{
    ExampleFrameListener(RenderWindow* win, Camera* cam, 
                         bool bufferedKeys = false, bool bufferedMouse = false,
                         bool bufferedJoy = false )


    virtual ~ExampleFrameListener();

    bool frameStarted (FrameEvent &evt);
    bool frameEnded (FrameEvent &evt);

    
}

```



ExampleFrameListener 的 frameStarted函数的主要功能是根据键盘和鼠标输入情况控制摄象机，其实你可以在实际应用的时候，在派生你自己的myFrameListener后，重新实现frameStarted函数，让其控制某些3D物体的自动动画、自动运动等。当然不要忘了还要让新的frameStarted函数调用基类ExampleFrameListener类中的frameStarted函数，不然你的键盘和鼠标控制功能就全部丢失了


## OGRE中的ExampleFrameListener类 ##

ExampleFrameListener类派生自FrameListener类，主要作用是监听系统输入，并对场景做出控制反应。对于非控制性的变化（如自动的动画），其状态更新也可以由ExampleFrameListener完成。






# Reference #
  * [OGRE中的ExampleFrameListener类详解](http://hi.baidu.com/hy469680890/item/f771d8159c31b8453a176e79)
  * [RenderTarget listener](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Intermediate+Tutorial+7&structure=Tutorials)