# todolist #

  * MultiTexture 例子

  * [实现动态纹理作为验证](http://blog.csdn.net/programrookie/article/details/4552447)


# 使用样例 #

```

  Material *mat = MaterialManager::getInstance()->createMaterial();
  mat->setShader(shaderProgram);

  //mat->setTexture(tex);   /* old job*/  
  mMat->createTextureUnitState( “xue.jpg” );

```


# Material/TextureUnitState #

```

class Material
{
private:
    TPtrArray*     mTextureUnitStates;

    TextureUnitState* searchTextureUnitState(char *name) const;

public:
    TextureUnitState* createTextureUnitState(char *name);
    Bool addTextureUnitState(TextureUnitState *texUnitState);
    Uint getTextureUnitStateSize();
    TextureUnitState* getTextureUnitState(char *name);
    TextureUnitState* getAllTextureUnitStates(Uint index);
}

enum TextureType
{
    T3D_TEXTURE_1D,
    T3D_TEXTURE_2D,
    T3D_TEXTURE_3D
};

enum TextureParameterName
{
    T3D_TEXTURE_MAG_FILTER,
    T3D_TEXTURE_MIN_FILTER,
    T3D_TEXTURE_WRAP_S,
    T3D_TEXTURE_WRAP_T
};

enum TextureParameterVal
{
    /* The following parameters are applicable to T3D_TEXTURE_MAG_FILTER. */
    T3D_NEAREST,
    T3D_LINEAR,

    /* The following parameters are applicable to T3D_TEXTURE_MAG_FILTER and T3D_TEXTURE_MIN_FILTER. */
    T3D_NEAREST_MIPMAP_NEAREST,
    T3D_LINEAR_MIPMAP_NEAREST,
    T3D_NEAREST_MIPMAP_LINEAR,
    T3D_LINEAR_MIPMAP_LINEAR,

    /* The following parameters are applicable to T3D_TEXTURE_WRAP_S and T3D_TEXTURE_WRAP_T. */
    T3D_REPEAT,
    T3D_CLAMP_TO_EDGE,
    T3D_MIRRORED_REPEAT
};

class TextureUnitState
{
private:
    char       mName[MAX_NAME_LEN];
    TPtrArray* mTextures;
    Uint       mUnitID;

    TextureType         mType;
    TextureParameterVal mTexMinFilter;
    TextureParameterVal mTexMagFilter;
    TextureParameterVal mTexWrapS;
    TextureParameterVal mTexWrapT;

protected:

public:
    TextureUnitState();
    TextureUnitState(char *name);
    ~TextureUnitState();

    void setName(char *name);
    void setID(Uint id);

    void setTexture(char *name);
    void setTexture(Texture *pTexture);
    void removeTexture(Texture *pTexture);

    const Uint getTextureCount() const;
    Texture* getAllTextures(Uint *count);

    void setTextureType(TextureType target);
    void setTextureParameter(TextureParameterName name, TextureParameterVal val);
    void setTextureParameter(TextureParameterVal minFilterVal,TextureParameterVal magFilterVal,TextureParameterVal wrapSVal, TextureParameterVal wrapTVal);

    const char* getName();
    const Uint getID();
    TextureType getTextureType();
    TextureParameterVal getTextureParameter(TextureParameterName name);
    void getTextureParameter(TextureParameterVal minFilterVal,TextureParameterVal magFilterVal,TextureParameterVal wrapSVal, TextureParameterVal wrapTVal);

    Uint getTextureCount();
    //const Texture* getTextures(char *name);
    Uint getTextureSize();
    const Texture* getTextures(Uint index);
};
 
```

# TextureManager/Texture #

```
//此部分暂未作改变
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


# World/Renderer #

```
class Renderer 
{
    void setTextureUnitSettings(TextureUnitState *texUnitState);


private:
    Uint getRealRenderMode(RenderMode mode);

    /* convert blenging factor to the value which the hardware support. */
    Uint getRealBlendFactor(BlendingFactor srcFactor);
    /* convert blenging mode to the value which the hardware support. */
    Uint getRealBlendMode(BlendingMode mode);

    Uint getRealTextureUnit(Uint texUnit);
    Uint getRealTextureType(TextureType target);
    Uint getRealTextureParameterName(TextureParameterName name);
    Uint  getRealTextureParameterVal(TextureParameterVal val);
}

void Renderer::setTextureUnitSettings(TextureUnitState* texUnitState)
{
    Uint target;
    Uint parameterName;
    int  parameterVal;
    Uint count, i, unit;
    const Texture *tex;

    /* active the texture unit */
    unit = texUnitState->getID();
    glActiveTexture( getRealTextureUnit(unit) );

    /* get the target */
    target = getRealTextureType(texUnitState->getTextureType());

    /* set parameters */
    parameterName = getRealTextureParameterName(T3D_TEXTURE_MAG_FILTER);
    parameterVal = getRealTextureParameterVal(texUnitState->getTextureParameterVal(T3D_TEXTURE_MAG_FILTER));
    glTexParameteri(target, parameterName, parameterVal);

    parameterName = getRealTextureParameterName(T3D_TEXTURE_MIN_FILTER);
    parameterVal = getRealTextureParameterVal(texUnitState->getTextureParameterVal(T3D_TEXTURE_MIN_FILTER));
    glTexParameteri(target, parameterName, parameterVal);

    parameterName = getRealTextureParameterName(T3D_TEXTURE_WRAP_S);
    parameterVal = getRealTextureParameterVal(texUnitState->getTextureParameterVal(T3D_TEXTURE_WRAP_S));
    glTexParameteri(target, parameterName, parameterVal);

    parameterName = getRealTextureParameterName(T3D_TEXTURE_WRAP_T);
    parameterVal = getRealTextureParameterVal(texUnitState->getTextureParameterVal(T3D_TEXTURE_WRAP_T));
    glTexParameteri(target, parameterName, parameterVal);

    /* bind each texture */
    count = texUnitState->getTextureSize();
    for(i=0;i<count;i++)
    {
        tex = texUnitState->getTextures(i);
        glBindTexture(target, tex->getTextureID());
    }

    return;
}

void World::renderOneObject ()
{
    Uint i, count = 0;
    TextureUnitState *texUnits = NULL;
    texUnits = mat->getAllTextureUnitStates(&count);

    ...
    count = mat->getTextureUnitStateSize();
    for(i=0; i<count; i++)
    {
        texUnits = mat->getTextureUnitStates(i);
        mRenderer.setTextureUnitSettings(texUnits);
    }

    mRenderer.render (ro);
    ...
}

```