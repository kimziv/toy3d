# OGREs设计思路 #

camera, light 从 SceneManager 创建

scene node 与 mesh 分离，entity attach 到 scene node里

Material: 在ogre里面Material的含义不再只是包含光照信息的那个Material的含义了。ogre把texture也加入到了Material里面(还有其他的很多的信息)，这样对于同一种Material最多只用调用一次setmaterial和settexture。(见reference1)

# SceneNode/Entity/Mesh/Submesh #

Mesh: ogre的mesh由一个或者多个submesh构成，每个submesh就对应一个Material，绘制的时候submesh是一个基本的单元。(见reference1)

Entities 是以 Meshes 作为自身基础的，Mesh 对象包括了一整套用来描述自身模型的数据。多个Entities 可以共用一种网格，比如，常常会在一个场景下创建同一种对象的多个拷贝。
[entity, mesh, submesh 的关系](http://www.cnblogs.com/leisure/archive/2012/06/29/2568915.html)

```
    Ogre::Entity* entNinja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
    entNinja->setCastShadows(true);
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);
 
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
 
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
 
    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);

```

# Mesh/SubMesh/Entity #



一般一个 Mesh 包含多个 SubMesh，如汽车模型，会分成车身、进气格栅、轮子、....

Entity 和 SubEntity是物体渲染特性的入口，Mesh 和 SubMesh 是物体结构特性（几何数据）的入口


```

class Entity {

   typedef std::vector<SubEntity*> SubEntityList;
   SubEntityList mSubEntityList;

}

class SubEntity {

        MaterialPtr mpMaterial;

        // Pointer to the SubMesh defining geometry.
        SubMesh* mSubMesh;


}


class SubMesh {

    RenderOperation::OperationType operationType;

    VertexData *vertexData;
    IndexData *vertexData;

    char* mMaterialName;
    
};


class Mesh {

    typedef std::vector<SubMesh*> SubMeshList;
    SubMeshList mSubMeshList;

    typedef HashMap<String, ushort> SubMeshNameMap ;
    SubMeshNameMap mSubMeshNameMap ;

    /// Local bounding box volume
    AxisAlignedBox mAABB;
    
    /// Local bounding sphere radius (centered on object)
    Real mBoundRadius;
    
};


```

# Mesh/SubMesh/VertexData/IndexData/VertexDeclaration/Material #


VertexData 是数据buffer，顶点、纹理、法线会存在一个buffer里

VertexDeclaration 记录了 buffer 里的数据布局：

```

//create mesh
Ogre::Mesh* mMesh = Ogre::MeshManager::getSingleton().createManual(yourMeshName, "General");

//create submesh
Ogre::SubMesh* mSubMesh = mMesh->createSubMesh(yourSubMeshName);


//create vertex declaration

Ogre::VertexData* data = new Ogre::VertexData();

#ifdef SHARED_GEOMETRY
     mMesh->sharedVertexData = data;
 #else
     mSubMesh->useSharedVertices = false; // This value is 'true' by default
     mSubMesh->vertexData = data;
 #endif

data->vertexCount = iVertexCount;

Ogre::VertexDeclaration* decl = data->vertexDeclaration;

size_t offset = 0;
 decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
 offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
 decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
 offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
 decl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
 offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
 decl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES, 1);

//create vertex buffer

Ogre::HardwareVertexBufferSharedPtr vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
     decl->getVertexSize(0),                     // This value is the size of a vertex in memory
     iVertexNbr,                                 // The number of vertices you'll put into this buffer
     Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY // Properties
 );


array[0] = vertices[1].x
 array[1] = vertices[1].y
 array[2] = vertices[1].z
 array[3] = vertices[1].normal.x
 array[4] = vertices[1].normal.y
 array[5] = vertices[1].normal.z
 
 array[6] = vertices[2].x


vbuf->writeData(0, vbuf->getSizeInBytes(), array, true);

 Ogre::VertexBufferBinding* bind = data->vertexBufferBinding;
 bind->setBinding(0, vbuf);

//create index buffer

Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
     Ogre::HardwareIndexBuffer::IT_16BIT,        // You can use several different value types here
     iIndexNbr,                                  // The number of indices you'll put in that buffer
     Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY // Properties
 );

//Bounding box and sphere
mMesh->_setBounds(Ogre::AxisAlignedBox(xMin,yMin,zMin,xMax,yMax,zMax));
 mMesh->_setBoundingSphereRadius(std::max(xMax-xMin, std::max(yMax-yMin, zMax-zMin))/2.0f);


mMesh->load();

//create material
Ogre::MaterialPtr mMat = Ogre::MaterialManager::getSingleton().create(yourMaterialName, "General", true);

//create technique
Ogre::Technique* mTech = mMat->createTechnique();

//create pass
Ogre::Pass* mPass = mTech->createPass();



//create texture unit
Ogre::TextureUnitState* mTexUnitState = mPass->createTextureUnitState();

//set color
mPass = mMat->getTechnique(0)->getPass(0);
 mPass->setDiffuse(Ogre::ColourValue(red, green, blue, alpha));


//set texture
Ogre::TexturePtr mTex = Ogre::TextureManager::getSingleton().load(yourTextureFileName, "General");
mPass->createTextureUnitState()->setTextureName(mTex->getName());

```

[Manual Resource Loading](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Manual+Resource+Loading&structure=Tutorials)

# material-technique-pass #

基本概念：
  * Pass是最基本的绘制单元，同时也是Renderable（可绘制对象）用来标识自己绘制状态的基本单元。
  * Technique是对Pass的集中管理，同时引入了硬件的考量
  * Material是管理的Technique的类
  * MaterialManager，对Material进行管理。主要实现了对纹理过滤的设置、Scheme的管理，设置相应的监听等操作。还负责读取材质脚本、初始化材质资源。


包含关系：
  * 1Material->n Techinque->(n Pass + extra params)->(n TextureUnit + m or 0 shaderUnit + n RenderStates（部分）)
  * Pass里的TextureUnit又包含了这一组texture的相关信息和设置，TexcoordSet, AddressMode, FilterSetting等等，
  * ShaderUnit则是对应于vs，fs以及新的gs，普通点也就最多两组。
  * shaderUnit包含了具体的shader和其shaderParams，为何要把shader和shaderParams分开呢，不说设计优雅的考虑，简单的说就是方便，很多时候params可能会需要共享，譬如shaderA里用到mvpMat，和eyePos， diffuse,specular,可能shaderB也只用到这些，但是两个shader的内部计算并不相同。


ogre的material system还是相当易读的，也是因为这些模块相互关系几乎都是单向的，我们开始编写的时候可以先不考虑Technique，就是直接1 Material->n Pass->...当然甚至你都可以把multi pass去掉,就等同于1个pass，当然由于pass都代码实际也没多少，我们还是加上好了。


原始渲染的伪代码就是：

```

for each pass
{
  setRenderStates(like alphe belnd, depth..)

  for each texture unit
    setTexSettings();

  if(hasVertexShader())
  {
    bindVertexShader();
    setShaderParams(vs);
  }

  if(hasFragmentShader())
  {
    bindFragmentShader();
    setShaderParams(fs);
  }

  drawPrimitives();

}

```

# pass/renderoperation/render system #
  * pass 保存了渲染状态
  * RenderOperation 保存了顶点数据
  * pass 的状态通过调 renderer 的 setXXX 接口放进去
  * RenderOperation 的数据流在 RenderOperation 里传进去

```

    renderSingleObject (Renderable *rend, Pass* pass, ...);

    manualRender (RenderOperation* rend, Pass* pass, 
        Matrix4& worldMatrix, Matrix4& viewMatrix, Matrix4& projMatrix,
        bool doBeginEndFrame)


```

manualRender

```


void sceneManager::updateGpuProgramParams ()
{

    if (mGpuParamsDirty)
        pass->_updateAutoParams(mAutoParamDataSource, mGpuParamsDirty);

    if (pass->hasVertexProgram())
    {   
         mDestRenderSystem->bindGpuProgramParameters(
                GPT_VERTEX_PROGRAM,     
                pass->getVertexProgramParameters(), 
                mGpuParamsDirty);
         }

 
         if (pass->hasFragmentProgram())
         {
             mDestRenderSystem->bindGpuProgramParameters(
                 GPT_FRAGMENT_PROGRA     M,
                 pass->getFragmentProgramParameters(),   
                 mGpuParamsDirty);
         }    
    }
}

Pass* sceneManager::_setPass (Pass *pass, ...)
{

    if (pass->hasVertexProgram())
        renderer->bindGpuProgram (pass->getVertexProgram());


    if (pass->hasFragmentProgram())
        renderer->bindGpuProgram (pass->getFragmentProgram());

    
    renderer->_setSceneBlending(pass->getSourceBlendFactor(), pass->getDestBlendFactor());

}


void sceneManager::manualRender (RenderOperation* rend, Pass* pass, Viewport *vp,
        Matrix4& worldMatrix, Matrix4& viewMatrix, Matrix4& projMatrix,
        bool doBeginEndFrame)
{
    renderer->_setViewPort(vp);

    if (doBeginEndFrame)
        renderer->_beginFrame();


    not need
    mDestRenderSystem->_setWorldMatrix (worldMatrix);
    setViewMatrix (viewMatrix);
    mDestRenderSystem->_setProjectionMatrix (projMatrix);


    _setPass (pass);

   
    if (pass->isProgrammable()) {

        mAutoParamDataSource->setWorldMatrix (world);
        Camera dummyCam ();
        dummyCam.setCustomViewMatrix (view);
        dummyCam.setCustomProjMatrix (proj);
        mAutoParamDataSource->setCurrentCamera (&dummyCam);
        updateGpuProgramParamers (pass);

    }
    
    renderer->_render(ro);
    
    renderer->endFrame();
}




```


# Resource #

> texture 是个资源
> texture state 是个 material
> texture id 如何跟 mesh 关联起来


# 多流技术 #

ogre使用了多流的技术，把vertex的positon，normal，texcord这些数据分开，放到多个流里面进行渲染，这方面的技术可以参考[D3D中多流的用法](http://dev.gameres.com/Program/Visual/3D/multistream.htm)。(见reference1)

# SceneManager渲染 #

OGRE 渲染总流程

从OGRE的例子中我们可以发现，在初始化完成之后，OGRE通过调用startRendering进行消息循环，然后调用renderOneFrame，通过RenderSystem的\_updateAllRenderTargets方法，更新所有的RenderTarget。RenderTarget通过update方法更新与之关联的Viewport并产生FPS统计信息。而Viewport则调用与之关联的Camera的\_renderScene方法进行渲染，Camera此时把“球”踢给SceneManager。进入SceneManager的renderScene成员函数中后，在经过“漫长”的计算后，把需要渲染的场景送给RenderSystem去做真正的渲染（至于怎么渲染暂且放过），此时我们可以看到熟悉的\_breginFrame和\_endFrame。


SceneManager渲染流程

_renderScene->findVisibleObjects->_renderVisibleObjects->renderQueueGroupObjects->renderObjects->renderSingleObject


```



void SceneManager::_renderScene()
{
    // Set the viewport
    setViewport(vp);


    // Set camera window clipping planes (if any)
    ....

    // Clear the render queue
    getRenderQueue()->clear();

    // Parse the scene and tag visibles
    _findVisibleObjects(camera,
        mIlluminationStage == IRS_RENDER_TO_TEXTURE? true : false);


    // Begin the frame
    mDestRenderSystem->_beginFrame();


    // Render scene content 
    _renderVisibleObjects();

    // End frame
    mDestRenderSystem->_endFrame();

}

void SceneManager::renderObjects(RenderablePassMap& objs)
{
    for (map) {
        renderSingleObject(renderalbe, pass, ...);
    }
}


void SceneManager::renderSingleObject(Renderable* rend, Pass* pass, ...)
{
    
}




```


# OGRE 渲染过程 #

OGRE 渲染过程(见reference1)：

在ogre里面，场景组织成一棵树形结构，而每一个可以画到屏幕上的物体都是一个renderable，在渲染的时候，ogre遍历场景树，利用剪裁算法（最基本的就是基于视锥的剪裁算法）剔出完全不可见的renderable，把可见的renderable放如到渲染队列里面，最后把渲染队列里面的renderable按照需要进行渲染。


渲染队列保存了所以这一次必须要渲染的物体的信息。它的构成比较的复杂，渲染队列被分成了好多个组（group），这些group都和一个id对于，越小GroupId的group就越先渲染。而每个group又被分成了很多个PriorityGroup，每一个PriorityGroup同样对于一个id，同样是越小的id就越先渲染。而PriorityGroup就是比较基本的渲染单元了。经过两次划分以后为于同一个PriorityGroup的renderable再次分组，这是因为透明物要进行特殊的处理，需要作透明处理的renderable进入一个vector，不要作透明处理的renderable按照它的Material进行分类，有着相同的Material的renderable进行同一个vector。到了最后渲染的时候，按照id遍历每个group，对于每个group，按照id遍历PriorityGroup，对于每个PriorityGroup，首先执行不透明物体的处理，然后把透明物体按照相对摄像机的远近进行排序，依次渲染每一个renderable，然后重复下一个PriorityGroup，然后是group。(见reference1)

下面是ogre的渲染伪代码。

```

for 每一个group
{
　　for 每一个 PriorityGroup
　　{
　　　　// 不透明部分
　　　　for 对于每一种Material
　　　　{
　　　　　　SetMaterial() // 包括了texture等等的属性
　　　　　　for 所有这种Material的Renderable
　　　　　　{
　　　　　　　　渲染这个renderable
　　　　　　}
　　　　}

　　　　// 透明部分
　　　　sort()
　　　　for 每一个renderable
　　　　{
　　　　　　SetMaterial()
　　　　　　渲染这个renderable
　　　　}
　　}
}


```



为什么要把renderable的优先顺序分成两级？比如把3D物品放到同一个group里面，而2D界面放到一个group里面，这样两个group就可以不受对方的影响，各自安排自己的子优先级。



# AutoConst/RealConstant/IntConstant #


[ogre glsl example](http://www.ogre3d.org/docs/manual/manual_21.html)



[沿着ogre实现 material system](http://www.cppblog.com/cty41/archive/2011/04/18/144448.html)

ogre 1.7.8 版本：

```


struct RealConstantEntry
{
    float val[4];
    bool isSet;
    RealConstantEntry() : isSet(false) {}
};

struct IntConstantEntry
{
    int val[4];
    bool isSet;
    IntConstantEntry() : isSet(false) {}
};


class _OgreExport GpuProgramParameters {

    typedef std::vector<RealConstantEntry> RealConstantList;
    typedef std::vector<IntConstantEntry> IntConstantList;

    // Auto parameter storage
    typedef std::vector<AutoConstantEntry> AutoConstantList;

    /// Packed list of floating-point constants
    RealConstantList mRealConstants;

    /// Packed list of integer constants
    IntConstantList mIntConstants;

    /// List of automatically updated parameters
    AutoConstantList mAutoConstants;

    /// Mapping from parameter names to indexes - high-level programs are expected to populate this
    typedef std::map<String, size_t> ParamNameMap;
    ParamNameMap mParamNameMap;


    void setNamedConstant(const String& name, Real val);
    void setNamedConstant(const String& name, int val);

    void setConstant(index, float,);
    void setConstant(index, double,);
    void setConstant(index, int,);


    
}

```

# GLSLES #

ogre\_src\_v1-8-1/RenderSystems/GLES2/src/GLSLES




```


/// Structure used to keep track of named uniforms in the linked program object
struct GLUniformReference
{
    /// GL location handle
    GLint mLocation;
    /// Which type of program params will this value come from?
    GpuProgramType mSourceProgType;
    /// The constant definition it relates to
    const GpuConstantDefinition* mConstantDef;
};



class GLSLESProgramCommon {

    /// Container of uniform references that are active in the program object
    GLUniformReferenceList mGLUniformReferences;

    /// Linked vertex program
    GLSLESGpuProgram* mVertexProgram;

    /// Linked fragment program
    GLSLESGpuProgram* mFragmentProgram;

    /// Flag to indicate that uniform references have already been built
    bool mUniformRefsBuilt;

    /// GL handle for the program object
    GLuint mGLProgramHandle;

    /// Flag indicating that the program or pipeline object has been successfully linked
    GLint mLinked;





};

void GLSLESProgramPipeline::buildGLUniformReferences(void)
{
}

void GLSLESProgramPipeline::updateUniforms(GpuProgramParametersSharedPtr params,
                                           uint16 mask, GpuProgramType fromProgType)
{
}




/*
 * update GpuProgramParameters 会调到 updateUniforms
void SceneManager::updateGpuProgramParameters(const Pass* pass)
*/

void GLSLLinkProgram::updateUniforms (GpuProgramParametersShaderPtr params, mask, GpuProgramType)
{

}




```


# Pass/TextureUniteState/TextureManager/Texture #

## 一个例子 ##

```

MaterialPtr mMat = MaterialManager::getSingleton().create( fileName, groupName, false );

  Pass *mPass = mMat->getTechnique(0)->getPass(0);
  mPass->setAlphaRejectSettings( CMPF_GREATER, 150 );
  mPass->setCullingMode( CULL_NONE );
  TextureUnitState *texState = mMat->getTechnique(0)->getPass(0)->createTextureUnitState( “xue.jpg” );

```

textureArray

ogre sample : texture array

## 纹理的载入 ##

```

class Pass
{
    vector<TextureUinit*> mTextureUnitStates;

    TextureUnitState* createTextureUnitState ();
    TextureUnitState* createTextureUnitState (string name， unsigned short texCoordSet);
    void addTextureUnitState (TextureUnitState *state);
    TextureUnitState* getTextureUnitState (index);
    TextureUnitState* getTextureUnitState (name);
        
}



class TextureUnitState 
{
 
    vector<string>  mFrames;
 
    vector<Texture*> mFramesPtrs;
 


    void setTextureName (name);

    void setTexture(Texture* tex);

}
 


class TextureManager 
{
 
    ResourceMap  map;

    size_t mMemoryBudget;  //in bytes
    size_t mMemoryUsage;   //in bytes
 

    void setMemoryBudget ();
    size_t getMemoryBudget();
    size_t getMemoryUsage ();
 


    Resource* create (name);  //create a new blank resource, but does not immediately load it
 
    Resource* getByName (name);  


    Resource* createOrRetrieve(name);   //getByName return NULL, then call create


    void remove(Resource* r);   //unload and remove from list
 
    void remove (name);
 


    void removeAll();
 
    void removeUnreferencedResources();
 


    void unload (name);  //not removed, simply free up their memory
 

    void unloadAll();
 
    void reloadAll();
 
    unloadUnreferencedResource();
 
    reloadUnreferencedResource();
    


    bool resoureExist(name);
 

    Texture* prepare (name, );  //load images only, not opengl object
 

    Texture* load (name, numMipmaps, ...); //load into openg object.
 
    Texture* loadImage(name, Image &img, ...);
 
    Texture* loadRawData (name, width, height, format, ...); 

    Texture* createManal(name, w, h, d, rgba, ....);
 
}
 
class Texture
{
 
    GLuint mTextureID;
 
    vector <Image> mLoadedImages;
 

    void prepare();  //load image file to image
 
    void load();
 


    void unload();   // call freeInternalResources
 

    void loadImage(Image& img);     //generate gl texture object
 
    void loadRawData(w, h, format, data);     //generate gl texture object
 

    void createInternalResources ();  //generate gl texture object
    void freeInternalResources ();   //delete opengl texture

}
 









```


## 纹理的绘制 ##


```

void SceneManager::renderOneObject ()
{
    for (all texture unit state) {
        renderer->setTextureUnitSettings (unit, pTex);
    }
}

RenderSystem::_setTextureUnitSettings(texUnit, TextureUnitState* tl)
{
    tex = tl._getTexturePtr();
    _setTexture (texUnit, tex);
    _setTextureCoordSet(texUnit, tl.getTextureCoordSet());
    _setTextureFiltering(texUnit, 
            tl.getTexureFiltering(FT_MIN), 
            tl.getTexureFiltering(FT_MAG), 
            tl.getTexureFiltering(FT_MIP));
    _setTextureLayerAnisotropy(texUnit, tl.getTextureAnisotropy());
    _setTextureMipMapBias(texUnit, tl.getTextureMipmapsBias());
    _setTextureBlendMode(texUnit, tl.getColourBlendMode());
    _setTextureBlendMode(texUnit, tl.getAlphaBlendMode());
    _setTextureXXXX....



}

GLES2RenderSystem::_setTexture (stage, enabled, texPtr)
{
    activateGLTextureUnit(stage);

    glBindTexture(texPtr);
    
}

```






# 最简单的 OGRE 程序 #

使用 ManualObject，加载纹理，显示cube，最简单的调用方式：

[学习OGRE： 绘制一个立方体ManualObject](http://hsw625728.blog.163.com/blog/static/39570728200910823457100/)

[学习OGRE：加上纹理](http://hsw625728.blog.163.com/blog/static/3957072820091084913370/)

# Pro OGRE Programming 笔记 #

[Pro OGRE Programming笔记系列](http://kun-111.blog.163.com/blog/static/40314793200781154032626/)

# 参考 #

  1. [ogre的图形渲染方式](http://gpgame.net/docs/program/ogre.htm)


# 其它引擎 #

## le3d ##

[opengl 基础知识培训](http://v.youku.com/v_show/id_XNDkxODc2MDUy.html)

## min3d ##

android 3d engine

## softart ##

http://code.google.com/p/softart/

## COCOS2DX ##

Cross platform open source 2D game engine

http://www.cocos2d-x.org/