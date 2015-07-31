# 参考资源 #
  * [Prefetching in a Texture Cache Architecture](http://graphics.stanford.edu/papers/texture_prefetch/texture_prefetch_down.pdf)



# todolist #

  * 将 TextureUnitState,TextureManager,Texture 集成进来

  * [实现动态纹理作为验证](http://blog.csdn.net/programrookie/article/details/4552447)


# TextureManager/Texture #

备份处理

```

class TextureManager 
{
 
    Map  mTexturePtrMap;

    size_t mMemoryBudget;  //in bytes
    size_t mMemoryUsage;   //in bytes
 

    void setMemoryBudget ();
    size_t getMemoryBudget();
    size_t getMemoryUsage ();
 


    Texture* create (name);  //create a new blank resource, but does not immediately load it
 
    Texture* getByName (name);  


    Texture* createOrRetrieve(name);   //getByName return NULL, then call create


    void remove(Texture* tex);   //unload and remove from list
 
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





# 资源管理策略 #
## Resource ##
  * 1 每个Resource有唯一的Name
  * 2 Resource有两种状态
> > 即：LoadingState和UsingState。二者分别表示资源的加载情况、使用情况。
  * 3 Resource的级别
> > 3.1 是否常用资源。
> > 3.2 空闲次数。这个值从零开始增加，表示在按照某个规则该资源未被使用的次数，由管理者通过接口维护。通过这一属性来提供一种老化机制。
  * 4 Resource类自己实现载入和卸载操作
  * 5 Resource必须在一段时间不使用时被删除，借助3.2来实现。

## ResourceManager ##
  * 1 所有ResourceManager都使用单例模式(Singleton)
  * 2 ResourceManager维护资源池，资源池保存已经创建的资源。
  * 3 ResourceManager负责Resource的创建和删除。
  * 4 ResourceManager提供资源池的管理策略。
  * 5 ResourceManager负责维护内存、显存预算
并根据实际情况维护这些预算值。

## TextureManager实现 ##
  * 一、内存、显存预算：
1 提供成员变量，记录最大、当前的可用内存、显存。

2 提供显存、内存预算设置接口。

3 引擎在创建、删除等操作时，根据消耗来维护当前可用内存、显存。

  * 二、纹理的存储和管理：
1 提供一个指针数组成员变量，存储创建的纹理，以下称为纹理数组。

2 管理策略：LRU。

2.1 纹理数组只允许在末尾追加元素，以使数组索引从低到高符合时间顺序；

2.2 当内存、显存足够使用时，直接加载、生成纹理；

2.3 当内存或者显存不够时，卸载或销毁某些纹理，以得到足够使用的内存或者显存；

2.4 当需要移除元素时，按照从后向前的顺序遍历顺组；

2.5 可以从任何位置移除元素，移除一个元素之后，其位置之后如果还有元素，这些元素将有序前移；

2.6 正在使用的纹理不能被移除；

2.7 移除纹理将先对优先级低的进行操作，当无可操作对象时，再考虑优先级高的；

2.8 当用户以像素数据的方式创建纹理时，用户传入的信息，包括width、height、pixel data、bytes per pixel，将以文件的方式被存储下来。

  * 三 提供纹理的创建、删除接口。
1 提供纹理的创建、删除接口。

2 提供纹理的加载、重加载、生成、销毁、卸载接口。

3 提供两个接口，分别设置文件存储目录、删除程序创建的纹理文件。


# Texture #
```

/*
 *  the definition of texture
 *  the base operation of texture :load, generate, degenerate, unload.
 */
class Texture 
{
    enum TextureLoadingState
    {
        TOY3D_UNLOADED,
        TOY3D_LOADED,
        //TOY3D_UNGENERATED,//this state maybe unnecessary.
        TOY3D_GENERATED
    };

    /*
    enum TextureParameterName
    {
        GL_TEXTURE_MAG_FILTER,
        GL_TEXTURE_MIN_FILTER,
        GL_TEXTURE_WRAP_S,
        GL_TEXTURE_WRAP_T
    };

    enum TextureParameterVal
    {
        GL_NEAREST,
        GL_LINEAR,
        GL_NEAREST_MIPMAP_NEAREST,
        GL_LINEAR_MIPMAP_NEAREST,
        GL_NEAREST_MIPMAP_LINEAR,
        GL_LINEAR_MIPMAP_LINEAR,
        GL_CLAMP,
        GL_REPEAT;
    };

    enum TextureDataType
    {
        GL_BYTE,
        GL_UNSIGNED_BYTE,
        GL_SHORT,
        GL_UNSIGNED_SHORT,
        GL_INT,
        GL_UNSIGNED_INT,
        GL_FLOAT,
        GL_FIXED
    };

    enum PixelFormat
    {
        GL_DEPTH_COMPONENT,
        GL_ALPHA,
        GL_RGB,
        GL_RGBA,
        GL_LUMINANCE,
        GL_LUMINANCE_ALPHA
    };

    typedef struct _TextureParameter
    {
        TextureParameterName paraName;
        TextureParameterVal paraVal;
        TextureDataType dataType;
        PixelFormat format;
    }TextureParameter;
    /*

    private:

    protected:
        /* the base member */
        char mName[MAX_NAME_LEN_BIG]; /* the resource file name */
        //char mFileName[MAX_NAME_LEN_BIG];

        Uint mTextureID;
        Uint mWidth;
        Uint mHeight;
        Uint mBytesPerPixel;
        unsigned char *mPixelData;

        //TextureParameter mParameter;

        /* the extended member */
        Bool mIsResident;
        volatile Uint mIdleLevel;
        volatile TextureLoadingState mLoadingState;
        volatile Bool mIsBeingUsed;

    public:
        //Texture();
        //Texture(char *pFileName);
        Texture(char *pFileName, Bool isResident = FALSE);
        ~Texture();

        /* 
         * The interfaces are used for textures created by the constructor with more than one parameter.
         */
        //Bool load();
        /*
         * The interface is used for textures created by the constructor with one parameter.
         */
        //Bool load(char *pFileName);
        Bool load(Image *image);
        Bool load(unsigned char *pImageData, Uint width, Uint height, Uint bytesPerPixel);

        Bool unload();

        Bool generate();
        Bool degenerate();

        void setIdleLevel(Uint value);

        const Bool isResident() const;
        const Bool getUsingState() const;
        const TextureLoadingState getLoadingState() const;
        const Uint getIdleLevel() const;

        const Uint getTextureID() const;
        const char* getTextureName() const;
        const char* getTextureResFileName() const;
}


```

# TextureManager #

类定义 TextureManager.h:

```

//TextureManager.h
class TextureManager
{

    enum TextureManageRule
    {
        T3D_LRU,
        T3D_FIFO
    };

    private:
        TextureManager();
        static TextureManager* mInstance;
        
        TPtrArray *mPtrArray;

        Uint mMemory;        /* the budget of memory */
        Uint mVMemory;       /* the budget of memory on vedio card */
        Uint mMemoryRest;    /* the rest of usable memory */
        Uint mVMemoryRest;   /* the rest of usable vedio card memory */

        char mDirName[MAX_NAME_LEN_BIG]; /* used for the files created by the constructor.*/

        //TextureManageRule mTMRule;

        /*
         * Fixme: Maybe the function should be privided in class Texture.
         */
        void deleteTextureFromGpu(Uint *texids, Uint count);

    protected:

    public:
        ~TextureManager();
        static TextureManager* getInstance();

        void setMemoryBudget(Uint value);  /* memory budget, unit MB */
        void setVMemoryBudget(Uint value); /* video card memory budget, unit MB */

        void setDirtory(char *pDirName);

        //void setTextureManagerRule(TextureManageRule rule = T3D_LRU);

        void create(char *pName);
        void create(char *pName, char *pResFileName, Bool isResident = FALSE);

        /*
         * Create a texture with tht state TOY3D_LOADED.
         * Attentions:
         * The information will be saved as *.tex in the directory mDirName.
         * So if you use the interface,
         * you should have the permissions to read and right the hardware.
         */
        const char* create(unsigned char *pImageData,Uint width, Uint height, Uint bytesPerPixel);

        Bool load(char *pName);
        //Bool load(Texture *pTexture);
        /* Reload all the textures which have been loaded. */
        Bool reload();

        Bool unload(char *pName);
        //Bool unload(Texture *pTexture);
        Bool unload(Uint idleLevel); /* It works, when the idleLevel is greater than 0 only. */

        Bool generate(char *pName);
        //Bool generate(Texture *pTexture);

        Bool degenerate(char *pName);
        //Bool degenerate(Texture *pTexture);
        Bool degenerate(Uint idleLevel); /* It works, when the idleLevel is greater than 0 only. */

        /* If the texture which you want to remove is being used, it will return false. */
        Bool remove(char *pName);
        //Bool remove(Texture *pTexture);
        /* If some of the texturesis being used, it will return false. */
        Bool removeAll();

        Bool removeFiles();

        const Uint getRestOfMemory() const;
        const Uint getRestOfVMemory() const;
};

```


类实现 TextureManager.cpp：

```

TextureManager* TextureManager::mInstance = NULL;

TextureManager* TextureManager::getInstance()
{

    if (NULL == mInstance)
        mInstance = new TextureManager();

    return mInstance;
}


TextureManager::TextureManager ()
{
}


TextureManager::~TextureManager ()
{
}


```

单件 TextureManager的使用：

```
    TextureManager::getInstance()->createTextureByFile("leaf.tga");
```


# 使用样例 #

```


//Examples

//You can use the TextureManager and Texture by the following ways.
//1st
Bool test(){
    Bool rv;
    Texture *texture = NULL;
    char textureName[MAX_NAME_LEN_BIG];
    Uint idleLevel;

    TextureManager::getInstance().setMemoryBudget(256);
    TextureManager::getInstance().setMemoryBudget(256);
    TextureManager::getInstance().setDirtory("E:\\test");

    strncpy(textureName, "E:\\test\\picture1.tga", MAX_NAME_LEN_BIG);
    texture = TextureManager::getInstance()->create(textureName);
    strncpy(textureName, "E:\\test\\picture2.tga", MAX_NAME_LEN_BIG);
    texture = TextureManager::getInstance()->create(textureName);
    ...

    //and you could load and generate the textures by the pointer when you use it.
    //Attention, textureName is a texture name which you know.
    if( TOY3D_LOADED == texture.getLoadingState() )
    {
        rv = TextureManager::getInstance()->load(textureName);
        if( True != rv )
            return False;
    }
    if( TOY3D_LOADED == texture.getLoadingState() )
    {
        rv = TextureManager::getInstance()->generate(textureName);
        if( True != rv )
            return False;
    }

    //Here is what you do by the textures.
    ......

    //If you want to unload or degenerate some textures in order to spare some memory/v-memory,
    //You can operate one texture by this.
    TextureManager::getInstance()->degenerate(textureName);
    TextureManager::getInstance()->unload(textureName);

    //And you can also operate some textures at a time as follows.
    idleLevel = 5;
    TextureManager::getInstance()->degenerate(idleLevel);
    TextureManager::getInstance()->unload(idleLevel);

    //When you finish what you want to do, you can remove the textures.
    //You can remove one and repeat the operation by this.
    rv = TextureManager::getInstance()->remove(textureName);
    if( True != rv )
    {
        return False;
    }

    //And you could remove all at a time as follows.
    rv = TextureManager::getInstance()->removeAll();
    if( True != rv )
    {
        return False;
    }

}

//2st
Bool test(){
    Bool rv;
    Texture *texture = NULL;
    char textureName[MAX_NAME_LEN_BIG];
    Uint idleLevel;

    unsigned char *pImageData;
    Uint width;
    Uint height;
    Uint bytesPerPixel;
    char *pFileName;

    TextureManager::getInstance().setMemoryBudget(256);
    TextureManager::getInstance().setMemoryBudget(256);
    TextureManager::getInstance().setDirtory("E:\\test");

    pImageData = ...
    width = ...
    height = ...
    bytesPerPixel = ...

    //You create a texture as follows.
    //Attentions: the texture created by this interface is in the state TOY3D_LOADED.
    pFileName = TextureManager::getInstance()->create(pImageData, width, height, bytesPerPixel);
    
    //You could do the other operation the same as the 1st way.
    ...
}

```