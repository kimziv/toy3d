# todo list #

ogre hardware buffer

http://blog.csdn.net/leonwei/article/details/5799770

ogre 中的动画

blog.csdn.net/leonwei/article/details/5819248



fbo 概念移留问题
  * 不 attach depth buffer，可以画出结果
  * 在attach多个texture时，只有第一个texture有内容。
  * attach 多个 texture，glDrawBuffer,glDrawBuffers  的使用
  * glDrawBuffer和 glDrawBuffers 在 opengl es 2.0 中不支持
  * 对于最简单最基本的 shader（如画三角形），不定义 shader 文件，可以正常显示吗？

toy3d
  * 支持多个 RenderTexture

渲染多个纹理，这个功能无法在一个FBO中一次完成。
参考 http://stackoverflow.com/questions/7892811/binding-multiple-buffers-in-opengl-es

  * 支持在一个 fbo 中 switch texture
  * 例子程序 map

hardware buffer 的引入


# 多个 render texture #
## 需求 ##

在 render texture 增加如下支持：
  * 同时画入多个纹理
  * 不同纹理画不同的内容
  * 多个 fbo 的支持


## 基本思路 ##
  * 切换 fbo 比在 fbo 内切换 texture 开销多很多，不推荐使用切 fbo
  * 一个 FBO，attach 上多个 texture，可实现同时画入多个纹理（定义一个render texture）
  * 一个 FBO，每次 attach 一个 texture，画完后切换纹理，再画，可实现不同纹理画不同内容(定义一个 render texture)
  * FBO 支持多个 color attachment point，即同时画到多个目标上
  * 用 glFramebufferTexture2D 切换 texture

glFramebufferTexture2D(GL\_FRAMEBUFFER, GL\_COLOR\_ATTACHMENT0, GL\_TEXTURE\_2D, textureId, 0);

The reason that a FBO has multiple color attachement points is to allow to render the color buffer to multiple destinations at the same time.

Switching framebuffer-attachable images is much faster than switching between FBOs. FBO provides glFramebufferTexture2D() to switch 2D texture objects, and glFramebufferRenderbuffer() to switch renderbuffer objects.





## toy3d lib 部分的修改(老版) ##

```

Bool RenderTexture::init()
{
    mFBO.init();
}

Bool RenderTexture::checkStatus()
{
    return mFBO.checkStatus();
}

// if not attached, attach the tex; 
// if attached, detach old one and attach new one 
void RenderTexture::attachTexture (Uint colori, Texture *tex)
{
    mFBO.attachTexture(colori, tex->getTextureId());
}

void RenderTexture::attachDepthBuffer(w, h)
{
    mFBO.attachDepthBuffer (w, h);
}

/*
void RenderTexture::selectDestination (Uint colori)
{
    glDrawBuffer (GL_COLOR_ATTACHMENT0 + colori);
}

void RenderTexture::selectMultipleDestination (Uint count, enum buffers)
{
    glDrawBuffers(count, buffers);
}
*/


```


## 使用样例 ##

```

    rt1 = world->createRenderTexture(tex1);
    rt1->addViewport (camera, t, l, w, h);

    rt2 = world->createRenderTexture(tex2)
    rt2->addViewport (camera, t, l, w, h);

    

```



## toy3d lib 部分的修改(新版) ##


TextureBuffer 的设计

```


class TextureBuffer
{
    TextureBuffer (GLenum target, GLuint id, GLint width, GLint height ...);
    ~TextureBuffer ();
    void bindToFramebuffer (GLenum attachment);

protected:
    GLenum mTarget;
    GLenum mFaceTarget;
    GLint mFace;
    GLint mLevel;

};

void TextureBuffer::bindToFramebuffer (GLenum attachment)
{
    glFramebufferTexture2D (GL_FRAMEBUFFER, attachment, mFaceTarget, mTexture2D, mLevel);   
}

```


RenderBuffer 的设计

```

class RenderBuffer 
{
    RenderBuffer (GLenum format, size_t width, size_t height, ...);
    virtual ~RenderBuffer();

    void bindToFramebuffer (GLenum attachment, ...);

protected:
    GLuint mRenderbufferID;
};


RenderBuffer::RenderBuffer()
{
    glGenRenderbuffers (1, &mRenderbufferID);
    GL_CHECK_ERROR;
    
    glBindRenderbuffer (GL_RENDERBUFFER, mRenderbufferID);
    GL_CHECK_ERROR;

    glRenderbufferStorage (GL_RENDERBUFFER， format, width, height);
    GL_CHECK_ERROR;
    
}


RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers(1, &mRenderbufferID);
    GL_CHECK_ERROR;
}

void RenderBuffer::bindToFramebuffer ()
{
    glFramebufferRenderbuffer (GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, mRenderbufferID);

    GL_CHECK_ERROR;
}


```


frame buffer object 封装


```

class FrameBufferObject
{
public:
    FrameBufferObject ();
    ~FrameBufferObject ();


    // Bind FrameBufferObject
    void bind();

  
    void attachTexture (Uint attachment, const TextureBuffer *tb);
    void detchTexture (Uint attachment);

    void attachDepthBuffer (RenderBuffer *db);
    void detachDepthBuffer ();

    
priate:
    GLuint mFB;
    RenderBuffer* mDepth;
    RenderBuffer* mStencil;

    TextureBuffer* mColour [TOY3D_MAX_FBO_ATTACHMENT];

    /** Initialise object.
        Must be called every time the bindings change.
        It fails with an exception if :
        - Attachment point 0 has no binding;
        - Not all bound surfaces have the same size
        - Not all bound surfaces have the same internal format
    */
    void initialise();
    

};

FrameBufferObject::FrameBufferObject ()
{
    /// Generate framebuffer object
    glGenFramebuffers(1, &mFB);
    GL_CHECK_ERROR;

    mDepth = NULL;
    mStecil = NULL;
    for (Uint x = 0; x < MAX_ATTACH_POINT; x++)
    {
        mColour[x] =NULL;
    }

}

~FrameBufferObject::FrameBufferObject ()
{
    mManager->releaseRenderBuffer (mDepth);
    mManager->releaseRenderBuffer (mStencil);

    glDeleteFramebuffers (1, &mFB);
    gl_CHECK_ERROR;





}


~FrameBufferObject::FrameBufferObject ()
{
    mManager->releaseRenderBuffer (mDepth);
    mManager->releaseRenderBuffer (mStencil);

    glDeleteFramebuffers (1, &mFB);
    GL_CHECK_ERROR;
}

void FrameBufferObject::initialise()
{
    mManager->releaseRenderBuffer (mDepth);
    mManager->releaseRenderBuffer (mStencil);

    if (!mColour[0]) {
        printf (Attachment 0 must have surface attached);
        return;
    }

    // Store basic stats
    Uint width = mColour[0]->getWidth();
    Uint height = mColour[0]->getHeight();
    GLuint format = mColour[0]->getGLFormat();

    glBindFramebuffer (GL_FRAMEBUFFER, mFB);
    GL_CHECK_ERROR;

    for (Uint x = 0; x < MAX_ATTACH_POINT; x++)
    {
        if (mColour[x]) {
            if (mColour[x]->getWidth() != width || 
                mColour[x]->getHeight() != height)
            {
                printf (Attachment x has incompatile size. 
                        It must be of the same as the size of surface 0);
                return;
            }
            if (mColour[x]->getGLFormat() != format)
            {
                printf (Attachment has incompatible format);
                return;
            }
            mColour[x]->bindToFramebuffer(GL_COLOR_ATTACHMENT0+x, mColor[x].zoffset);
          
        }
        else {
            glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+x, GL_RENDERBUFFER, 0);
            GL_CHECK_ERROR;
        }
    }


    /// Check status
    GLuint status;
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    GL_CHECK_ERROR;

    GL_CHECK_ERROR;

    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE:
        // All is good
        break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
         printf("All framebuffer formats with this texture internal format unsupported");
        default:
            printf("Framebuffer incomplete or other FBO status error");
    }    
}

void FrameBufferObject::bind()
{
    glBindFramebuffer (GL_FRAMEBUFFER, fb);
    GL_CHECK_ERROR;
}

void FrameBufferObject::attachTexture (Uint attachment, TextureBuffer *bf)
{
    if (attachment < T3D_MAX_ATTACH_POINT)
        return;

    mColour[attachment] = target;

    if (mColour[0])
        initialise();
}

void FrameBufferObject::detachTexture (Uint attachment)
{
    if (attachment < T3D_MAX_ATTACH_POINT)
        return;

    mColour[attachment] = 0;

    if (mColour[0])
        initialise();

}

void FrameBufferObject::attachDepthBuffer (RenderBuffer *db)
{
    glBindFramebuffer (GL_FRAMEBUFFER, mFB);
    GL_CHECK_ERROR

    if (db) {
        db->bindToFramebuffer (GL_DEPTH_ATTACHMENT, 0);
    }
    else {
        //deattach
        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_RENDERBUFFER, 0);
        GL_CHECK_ERROR;

    }
    
}


void FrameBufferObject::detachDepthBuffer ()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFB);
    GL_CHECK_ERROR;

    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0 );
    GL_CHECK_ERROR;
}



```


FBOManager 设计

```

class FBOManager
{
    FBOManager ();
    ～FBOManager();

    void bind (RenderTarget *target);

    // No-op for FBOs
    void unbind (RenderTarget *target) {};


    RenderTexture* FBOManager::createRenderTexture (name, TextureBuffer* tb, ...);
    MultiRenderTarget* createMultiRenderTarget (name);
    RenderBuffer* FBOManager::requestRenderBuffer (GLenum format, Uint width, Uint height, ...);  
    void releaseRenderBuffer (const RenderBuffer* rb);  

private:
    typedef map<RBFormat, RBRef>::type RenderBufferMap;
    RenderBufferMap mRenderBufferMap;
    
    
};

void FBOManager::bind (RenderTarget* target)
{
    FrameBufferObject *fbo = 0;
    fbo = target->getFBO();
    fbo->bind();

}


```

RenderSystem 部分

```

void renderer::setRenderTarget (RenderTarget* target)
{
    if (mActiveRenderTarget && mRTTManager)
        mRTTManager->unbind (mActiveRenderTarget);


    mActiveRenderTarget = target;
    mRTTManager->bind(target);

}

```





# change window size #

改变窗口大小时，图形无法自适应

lib部分

```

class RenderTarget {

    Viewport* getViewport(Uint index);
};

class Viewport {
    void setWidht(Uint);
    void setHeight(Uint);
};

```


example 部分

```

void changeSize(int w, int h)
{
    Viewport *vp = win->getViewport (0);
    vp->setWidth(width);
    vp->setHeight(height);

}


```


# toy3d 设计 #

## 现存的问题 ##

如何过滤出该画的对象？
  1. 道路画到 RTT1
  1. 建筑话到 RTT2
  1. 结果把纹理贴到四边形上

## FBO RenderTexture ##

例子代码：

```
   Texture *tex = TexturemManager:createTexture (RGBA, w, h);

   RenderTexture* rt = world->createRenderTexture(tex);
   rt->addViewport (camera, l, t, w, h);

```


外围代码：

```

Bool World::createRenderTexture (Texture *tex)
{
    mRenderer.createRenderTexture(tex);
}

Bool Renderer:createRenderTexture(Texture *tex)
{
   RenderTexture *rt = new RenderTexture ();
   Bool ret = rt->init (tex);
   if (!ret)
       delete rt;
    
   
}

void Renderer::setRenderTarget(RenderTarget *target)
{
    mActiveRenderTarget->unbind();    
    target->bind();
    mActiveRenderTarget = target;
}

```



RenderTexture 继承自 RenderTarget

```

    class RenderTexture : RenderTarget
    {
	private:
        FrameBufferObject mFBO;
        

        /* You can get width and height from the mTexture after the class Texture modified. */

    public:
        RenderTexture();
        ~RenderTexture();

        void init(Texture *tex);
        
        void bind();
        void unbind();
    };

    RenderTexture::RenderTexture (){}

    Bool RenderTexture::init (Texture *tex)

    {
        mFBO.bind();
        mFBO.attachTexture (tex->getId());
        mFBO.attachDepthBuffer(tex->getWidth(), tex->getHeight());
        return mFBO.checkStatus();
    }

    void RenderTexture::bind()
    {
        mFBO.bind();
    }

    class FrameBufferObject
    {
    private:

        Uint mFBOId;
        int mRBOId;


    public:
        FrameBufferObject();
        ~FrameBufferObject();

        void bind();
        void unbind();

        void attachDepthBuffer(Uint w, Uint h);

        void attachTexture(Uint textureId);

        void checkStatus();

        Uint getFboid() const;
    };

    FrameBufferObject::FrameBufferObject ()
    {
        mRBOid = -1;
        //create fbo
        glGenFraXXXXX..
    }

    FrameBufferObject::~FrameBufferObject ()
    {
        //delete rbo
        if (mRBOid >= 0)
            glDeleteRenderbuffers(1, &mRBOid);

        //delete fbo
        glDeleteFraXXXXX.
    }

    void FrameBufferObject::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fboId);
    }

 
    void FrameBufferObject::attachTexture(Uint id)
    {
    }

    void FrameBufferObject::attachDepthBuffer(w, h)
    {
       glXXXX
    }   

    void FrameBufferObject::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }







```




## 主循环 ##

```

World *world = NULL
Camera *camera = NULL;
RenderWindow* mWindow = NULL;

void init()
{
    //create camera
    camera = world->createCamera("Camera1");
    camera->setPosition(x, y, z);
    camera->lookAt();

    mWindow = world->createRenderWindow ();

    //create viewports
    Viewport *vp = mWindow->addViewport (camera, left, top, w, h);
    


}



void display()
{
    //fixme: where init targets
    world->renderOneFrame();
    
    glutSwapBuffers ();
}
 
```

RenderSystem 保存 target
  1. 按一定的顺序对 render target 进行 update
  1. render texture 在 render buffer 之前

## World ##

```

class World
{
    void renderOneFrame();
    RenderWindow* createRenderwindow ();
    RenderTexture* createRenderTexture ();

    void renderScene (Camera *camera, Viewport *vp);


}


void World::renderOneFrame() {

    // update all targets but don't swap buffers
    mRenderer->updateAllRenderTargets();

}

RenderWindow* World::createRenderWindow ()
{
    return mRenderer.createRenderWindow();
}

void World::renderScene (Camera* camera, Viewport *vp)
{
    ... ...
    mCurrentViewport = vp;
    mRenderer.setViewport (vp);
    ...
    render visible objects.
}

```

## Renderer ##

```

class Renderer {

private:
    RenderTargetArray renderTargets[SIZE];
    RenderTarget* mActiveRenderTarget;
    

public:
    //update all targets
    void updateAllRenderTargets();
    void setViewport (Viewport *vp);
    void setTarget(RenderTarget *target);

    void attachRenderTarget (RenderTarget &target);
    RenderTarget *detachRenderTarget (name);

    RenderWindow* createRenderWindow ();
    RenderTexture* createRenderTexture ();
};


void Renderer::updateAllRenderTargets()
{

    for (rende target array)
        target->update();

}


void Renderer::setViewport (Viewport *vp)
{

    RenderTarget *target = vp->getTarget();
    setTarget(target);

    glViewport (vp->x, vp->y, vp->w, vp->h );
    
}

void Renderer::setTarget(RenderTarget *target)
{

    // Unbind current frame buffer object
    if(mActiveRenderTarget && mRTTManager)
        mRTTManager->unbind(mActiveRenderTarget);

    mActiveRenderTarget = target;
    if (target)
    {
        // Switch context if different from current one
        GLES2Context *newContext = 0;
        target->getCustomAttribute("GLCONTEXT", &newContext);
        if (newContext && mCurrentContext != newContext)
            {
                _switchContext(newContext);
            }

        // Check the FBO's depth buffer status
        GLES2DepthBuffer *depthBuffer = static_cast<GLES2DepthBuffer*>(target->getDepthBuffer());

        if( target->getDepthBufferPool() != DepthBuffer::POOL_NO_DEPTH &&
                (!depthBuffer || depthBuffer->getGLContext() != mCurrentContext ) )
        {
            // Depth is automatically managed and there is no depth buffer attached to this RT
            // or the Current context doesn't match the one this Depth buffer was created with
            setDepthBufferFor( target );
        }

        // Bind frame buffer object
        mRTTManager->bind(target);
    }


}

RenderWindow* Renderer::createRenderWindow ()
{
    RenderWindow *win = new RenderWindow();
    attachRenderTarget ((RenderTarget &) *win);

    

}


```


## RenderTarget ##

RenderTarget
  1. 接收渲染结果
  1. 创建维护 Viewport
  1. 一个 Viewport 对应一个 Camera和一个 RenderTarget
  1. 一个 Camera 对应一个 Viewport
  1. 一个 RenderTarget 可拥有对个 Viewport，此功能在游戏中可用于多人对战时的分屏显示


```

class RenderTarget {

private:
   array viewports[MAX_SIZE];

public:
    void update();

    Viewport* addViewport (Camera *cam, float left, float top, float w, float h);

t
};

void RenderTarget::update()
{

    for (viewport array)
        viewport->update()

}

```



## Viewport ##

```

class Viewport 
{
private:
    Camera* mCamera;
    RenderTarget *mTarget;

    Real mLeft, mTop, mWidth, mHeight;

public:
    Viewport (Camera *camera, RenderTarget *target, 
              Real left, Real top, Real width, Real height);
    void update();
}

void Viewport::update()
{

    if (mCamera)
        mCamera->renderScence(this);

}

```


## Camera ##

```

Camera
{

    void renderScene(Viewport *vp);

}

void Camera::renderScene(Viewport *vp)
{

    //render scene
    mWorld->renderScene(this, vp);


}

```

## World ##

```

class World
{
    void renderScene(Camera *camera, Viewport *vp);

}

void World::renderScene (Camera *camera, Viewport *vp)
{

    mRenderer->setViewport (vp);

    mAutoParamDataSource->......

    mRenderer->begin();
    
    //render content
    renderVisibleObjects();

    mRender->end();
}



```

## RTTManager ##

```

class RTTManager::public Singleton<GLES2RTTManager>
{

    RenderTexture *createRenderTexture();
    void bind();
    void unbind();
    

}

```


# 样例 #

可做的样例：
  1. 镜面反射效果
  1. 地图

样例的实现：
  1. 2个 camera



# 简介 #

主要思路:
  * glCopyTexImage：把 framebuffer 的东西拷贝到纹理
  * Pbuffer
  * FBO
  * PBO

目前流行用 FBO。

参考资源1





# FBO基本渲染流程 #


```
    GLint fboId;
    glGenFramebuffers(1, &fboId);

    // set rendering destination to FBO
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);


    /* Draw base layer texture */
    glFramebufferTexture2D(...);
    
    //attach base layer texture
    glFrameBufferAttach (base_layer_texture);

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw();


    /* Draw road layer texture */

    //attach road layer texture
    glFrameBufferAttach (road_layer_texture);

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw();


    // unbind FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    
    //draw two textures  on two screen
     ...

    glDeleteFramebuffers(1, &fboId);

```

# OGRE 设计 #

```


class GLES2RTTManager : public Singleton<GLES2RTTManager>
{
    public:
        virtual ~GLES2RTTManager();

        virtual RenderTexture *createRenderTexture(const String &name, const GLES2SurfaceDesc &target, bool writeGamma, uint fsaa) = 0;

        /** Check if a certain format is usable as rendertexture format
        */
        virtual bool checkFormat(PixelFormat format) = 0;

        /** Bind a certain render target.
        */
        virtual void bind(RenderTarget *target) = 0;

        /** Unbind a certain render target. This is called before binding another RenderTarget, and
            before the context is switched. It can be used to do a copy, or just be a noop if direct
            binding is used.
        */
        virtual void unbind(RenderTarget *target) = 0;


        /** Create a multi render target
        */
        virtual MultiRenderTarget* createMultiRenderTarget(const String & name);

        /** Get the closest supported alternative format. If format is supported, returns format.
        */
        virtual PixelFormat getSupportedAlternative(PixelFormat format);
};






void GLES2RenderSystem::_setRenderTarget(RenderTarget *target)
{

    // Unbind frame buffer object
    if(mActiveRenderTarget && mRTTManager)
        mRTTManager->unbind(mActiveRenderTarget);

    mActiveRenderTarget = target;
    if (target)
    {
        // Switch context if different from current one
        GLES2Context *newContext = 0;
        target->getCustomAttribute("GLCONTEXT", &newContext);
        if (newContext && mCurrentContext != newContext)
        {
             _switchContext(newContext);
        }

        // Check the FBO's depth buffer status
        GLES2DepthBuffer *depthBuffer = static_cast<GLES2DepthBuffer*>(target->getDepthBuffer());

        if( target->getDepthBufferPool() != DepthBuffer::POOL_NO_DEPTH &&
                (!depthBuffer || depthBuffer->getGLContext() != mCurrentContext ) )
        {
            // Depth is automatically managed and there is no depth buffer attached to this RT
            // or the Current context doesn't match the one this Depth buffer was created with
            setDepthBufferFor( target );
        }

        // Bind frame buffer object
        mRTTManager->bind(target);
    }


}


viod GLES2RenderSystem::_setViewPort (Viewport *vp)
{

    if (!vp){
        mActiveViewport = NULL;
        _setRenderTarget (NULL);
    }
    else if (vp != mActiveViewport || vp->_isUpdated()) {

        RenderTarget *target;
        target = vp->getTarget();
        _setRenderTarget(target);
        mActiveViewport = vp;

        ... 
        glViewport (x, y,w, h);
        glScissor (x, y, w, h);
        ....


    }


}


void SceneManager::manualRender(Renderable* rend, const Pass* pass, Viewport* vp,
    const Matrix4& viewMatrix,
    const Matrix4& projMatrix,bool doBeginEndFrame,
    bool lightScissoringClipping, bool doLightIteration, const LightList* manualLightList)
{
    if (vp)
        mDestRenderSystem->_setViewport(vp);

    if (doBeginEndFrame)
        mDestRenderSystem->_beginFrame();

    setViewMatrix(viewMatrix);
    mDestRenderSystem->_setProjectionMatrix(projMatrix);

    _setPass(pass);
    Camera dummyCam(StringUtil::BLANK, 0);
    dummyCam.setCustomViewMatrix(true, viewMatrix);
    dummyCam.setCustomProjectionMatrix(true, projMatrix);
    // Do we need to update GPU program parameters?
    if (pass->isProgrammable())
    {
        if (vp)
        {
            mAutoParamDataSource->setCurrentViewport(vp);
            mAutoParamDataSource->setCurrentRenderTarget(vp->getTarget());
        }
        mAutoParamDataSource->setCurrentSceneManager(this);
        mAutoParamDataSource->setCurrentCamera(&dummyCam, false);
        updateGpuProgramParameters(pass);
    }
    if (vp)
        mCurrentViewport = vp;
    renderSingleObject(rend, pass, lightScissoringClipping, doLightIteration, manualLightList);


    if (doBeginEndFrame)
        mDestRenderSystem->_endFrame();

}




```


OGRE 渲染到纹理使用样例

```

//创建纹理
TexturePtr texture = TextureManager::getSingleton().createManual( "RttTex",

         ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D,

         512, 512, 0, PF_R8G8B8, TU_RENDERTARGET );


//创建摄像机和视口，保存到 render target 中
RenderTarget *rttTex = texture->getBuffer()->getRenderTarget();

mReflectCam = mSceneMgr->createCamera("ReflectCam");
mReflectCam->setNearClipDistance(mCamera->getNearClipDistance());
mReflectCam->setFarClipDistance(mCamera->getFarClipDistance());
mReflectCam->setAspectRatio(
                (Real)mWindow->getViewport(0)->getActualWidth() /
                (Real)mWindow->getViewport(0)->getActualHeight());
Viewport *v = rttTex->addViewport( mReflectCam );
v->setClearEveryFrame( true );
v->setBackgroundColour( ColourValue::Black );


创建使用渲染纹理的材质

MaterialPtr mat = MaterialManager::getSingleton().create("RttMat",
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

TextureUnitState* t = mat->getTechnique(0)->getPass(0)->createTextureUnitState("RustedMetal.jpg");

t = mat->getTechnique(0)->getPass(0)->createTextureUnitState("RttTex");

// Blend with base texture

t->setColourOperationEx(LBX_BLEND_MANUAL, LBS_TEXTURE, LBS_CURRENT,
            ColourValue::White,  ColourValue::White, 0.25);
t->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
t->setProjectiveTexturing(true, mReflectCam);

rttTex->addListener(this);

//set materila to entity
mPlaneEnt->setMaterialName("RttMat");

```


RenderTarget
  1. 接收渲染结果
  1. 创建维护 Viewport
  1. 一个 Viewport 对应一个 Camera和一个 RenderTarget
  1. 一个 Camera 对应一个 Viewport
  1. 一个 RenderTarget 可拥有对个 Viewport

```


class RenderTarget 
{
    ViewportList mViewportList;

    Viewport* addViewport (Camera *cam, int ZOrder, float f, t, w, h);


}

```



# Reference #
  * [OpenGL Frame Buffer Object 101](http://www.gamedev.net/page/resources/_/technical/opengl/opengl-frame-buffer-object-101-r2331)
  * [OpenGL Frame Buffer Object 201](http://www.gamedev.net/page/resources/_/technical/opengl/opengl-frame-buffer-object-201-r2333)
  * [opengl FBO](http://www.songho.ca/opengl/gl_fbo.html)
  * [OpenGL 中的 Render To Texture](http://blog.csdn.net/Nhsoft/article/details/1105309)
  * [Render to Texture with OpenGL ES](http://processors.wiki.ti.com/index.php/Render_to_Texture_with_OpenGL_ES)
  * [OGRE 渲染到纹理](http://blog.csdn.net/leonwei/article/details/5740728)
  * [学一学VBO](http://www.zwqxin.com/archives/opengl/learn-fbo.html)
  * [OGRE demo\_render\_to\_texture解析](http://blog.csdn.net/chengxu0921/article/details/4761387)
  * [OGRE的主要渲染流程](http://www.lihuasoft.net/article/show.php?id=4865)
  * [Ogre设计模式分析-观察者模式](http://blog.csdn.net/qq18052887/article/details/5438864)

  * [ogre分析之场景渲染](http://wenku.baidu.com/view/7e32972a0066f5335a8121ea.html###)