# 基本思想 #

总体来说：
  * 资源包括： mesh, shaderprogram, texture
  * 资源存在对应 Manager 的列表中
  * 每种资源对应一种 manager

具体来说：
  * Mesh 可以由多个 Entity 共享
  * ShaderProgram 可以由多个 Entity 共享
  * Texture 可以由多个 Entity 共享
  * 所有的 Mesh 都经过 MeshManager 创建与释放，并实际保存在里边
  * 所有的 ShaderProgram 都经过 ShaderProgramManager 创建与释放，并实际保存在里边
  * 所有的 Texture 都经过 TextureManager 创建与释放，并实际保存在里边


# 注意 #
  * 在 ShaderProgramManagers 里保存 Params 列表
  * Manager 的 create 接口貌似只返回指针，并没有保存在自己的里边
  * ResourceManager 还定义了 resouce pool map，有必要吗？

# 遗留问题 #
  * 当释放 manager 的某一个资源时，数组中间会空出来
  * 无法索引、查找资源
  * 每个 manager 调用 destroy 很繁琐
  * 各个 manager 开发给用户还是包到 root 里
  * 设计一个通用list，取代指针数组
  * Resource父类、ResouceManager 父类
  * world 里的 camera 是个对象，需要支持对个，并存指针


# MeshManager #

```

class MeshManager {

private:

   Mesh* mMeshes[MAX_MESH_COUNT];
   Uint mMeshCount;

public:

    Mesh* createMesh ();

    void destroyMesh(Mesh *mesh);
    void destroyAllMeshes ();

};




```


# ShaderProgramManager #

```

class ShaderProgramManager {

private:

   ShaderProgramParams *mShaderProgramParams[MAX_SHADER_PROGRAM_PARAMS_COUNT];
   int mShaderProgramParamsCount;

   ShaderProgram* mShaderPrograms[MAX_SHADER_PROGRAM_COUNT];
   Uint mShaderProgramCount;

public:

    ShaderProgram* createShaderProgam ();

    ShaderProgramParams* createShaderProgramParams();
    void destroyShadrProgramParams(ShaderProgramParams* parma);
    void destroyAllShaderProgramParams ();

    void destroyShaderProgram (ShaderProgram *prog);
    void destroyAllShaderPrograms ();

};



```


# TextureManager #

```

class TextureManager {

private:

   Texture* mTextures[MAX_TEXTURE_COUNT];
   Uint mTextureCount;

public:

    Texture* createTexture (const char* filename);

    void destroyTexture (Texture *tex);
    void destroyAllTextures ();

};

```



# MaterialManager #



```

class MaterialManager {

private:

   Material* mMaterials[MAX_MATERIAL_COUNT];
   Uint mMaterialCount;

public:

    Material* createMaterial ();

    void destroyMaterial (Material *mat);
    void destroyAllMaterials ();

};

```




# 用户使用 #

```

World *world = NULL;

void init ()
{

    world = new World ();
    world->setSize(w,h);
    world->setBackColor (r, g, b, a);

    Camera *camera = world->createCamera ();
    camera->lookAt (...);
    camera->perspective (...);


    ShaderProgramParam *param = 
        ShaderProgramManager::getInstance()->createShaderProgramParam();
    param->setAutoUniform (...);
    param->setCustUniform (...);
    param->setAttr(...);

    
    ShaderProgram *prog = 
        ShaderProgramManager::getInstance()->createShaderProgram();
    prog->bindShaderProgramParam(param);
  

    Texture *tex = TextureManager::getInstance()->createTextureByFile(filename);
    

    Material *mat = MaterialManager::getInstance()->createMaterial();
    mat->setShaderProgram (prog);
    mat->setTexture (tex);
  

    Mesh *mesh = MeshManager::getInstance()->creatMesh();
    mesh->setRenderMode (...);
    mesh->setVertices (...);
    mesh->setUVs (...);

  
    Entity *entity = world->createEntity ();
    entity->setMesh(mesh);
    entity->setMaterial (mat);
   
}

void display ()
{

    world->startRendering ();
    
    flush & swapBuffer 

}

void cleanup ()
{

    ShaderProgramManager::getInstance()->destroyAllShaderProgramParams();
    ShaderProgramManager::getInstance()->destroyAllShaderPrograms();
    TextureManager::getInstance()->destroyAllTextures();
    MaterialManager::getInstance()->destroyAllMaterials();
    MeshManager::getInstance()->destroyAllMeshes(); 
   
    world->destroyAllEntities();
}


```




# Reference #

  1. [你的引擎用不用stl boost？ 为什么？](http://www.opengpu.org/forum.php?mod=viewthread&tid=2737)


# Details #

Add your content here.  Format your content with:
  * Text in **bold** or _italic_
  * Headings, paragraphs, and lists
  * Automatic links to other wiki pages