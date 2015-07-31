# 遗留问题 #

  * setNamedAutoConstant 改名成 setNamedAutoUniformConstant
  * mat->loadTexture(filename);
  * 在 world 里 destroy entity
  * 在 entity 里 destroy material


# 基本思路 #

  * 增加 entity，entity 是基本的绘制单元
  * entity 包含 mesh 和 material
  * mesh 保存基本的几何数据
  * material 保存 shader,texture, material
  * 绘制时将需要绘制的数据传入 renderer



# Texture部分 #



做一个假设，每个 entity 只有一个 texture

```

void World::renderOneObject (RenderOperation* ro, Material* mat, 
        Real worldMatrix[16], Real viewMatrix[16], Real projMatrix[16])
{
    renderer->setViewPort(...);

    renderer->beginFrame();

    renderer->bindShaderProgram (...);

    renderer->updateAutoUniform(...);
    renderer->updateCustUniform ();

    renderer->setTexture(mat->getTexture());

    renderer->render(ro);
    
    renderer->endFrame();
}


void Renderer::setTexture(Texture* tex)
{

    if (tex) {

        glEnable(GL_TEXTURE_2D);
        unit = mCurrentProgram->getCustLoacation("SAMPLE2D");
        glActiveTexture （unit）；
        glBindTexture (GL_TEXTURE_2D, tex->getTextureID());
    }

}


void Renderer::render(RenderOperation* ro)
{

    ...
    pTempR = ro->getUVs();
    if( pTempR )
    {
        index = ro->getShaderAttribution( TOY3D_ATTR_UV );^M
        glVertexAttribPointer( index, 2, GL_FLOAT, 0, 0, pTempR );^M
        glEnableVertexAttribArray( index );^M
    }

    ...

    glDrawArrays( mode, 0,  ro->getVerticesCount() );^M
}



```


用户使用部分：

```


void init()
{
    Material *mat = entity->createMaterial();
    mat->setShaderProgram (shaderProgram);
    mat->loadTexture (name);
}

void destroy ()
{
    
   Material *mat = entity->getMaterial();
   mat->unloadTexture();
   
   world->destroyAllEntities();

} 
    

}




```



# Mesh #

```

class Mesh {

private:
    RenderMode mRenderMode;
    Real *mVertices;^M
    Real* mColors;^M
    Real* mUVs;^M
    Real* mNormals;^M

    Uint mVertexCount;


public:
   void getRenderOperation (RenderOpertation *op);
   void setVertices (...);
}

```

# entity #

```

class Entity {

private:
    Real mModelMatrix[MATRIX_4x4_SIZE];
    Mesh *mesh;
    Texture *tex;
    ShaderProgram *mShaderProgram;
    
    
public:
   void translate();
   void rotate();
   void scale ();

   void getRenderOperation (RenderOpertation *op);

   void setMesh (Mesh *mesh);
   void setMaterial (Material *mat);

};

```

# Material #


```
class material {

private:
    Texture *tex; 
    ShaderProgram *mShaderProgram;
    

    void setTexture (Texture *tex);

}

```

# world #

```

class World {

private:
   Entity *mEntities[MAX_ENTITY_COUNT];
    
   Real mWorldMatrix [MATRIX_4x4_SIZE];

public:

   Entity *createEntity (Mesh *mesh);

   
   void destoryAllCameras ();
   void destroyAllEntities ();


   void startRendering ();

}

/*
//tobe delere
void World::updateGpuProgramParameters (Material *mat)
{

    if (!mShaderParamsDirty)
        return;

    if (mShaderParamsDirty) ｛
        //write auto uniform to shader by param->update
        mat->updateAutoParams (mAutoParamDataSource, bool???);
    ｝

    renderer->bindGpuProgramParameters (mat->getProgramParameters(), bool???);

}

*/



void World::renderOneObject (RenderOperation* ro, Material* mat, 
        Real worldMatrix[16], Real viewMatrix[16], Real projMatrix[16])
{
    renderer->setViewPort(0, 0, mWidth,mHeight);

    renderer->beginFrame();


    renderer->bindShaderProgram (mat->getShaderProgram());


    mAutoParamDataSource.setWorldMatrix (worldMatrix);
    mAutoParamDataSource.setViewMatrix (viewmatrix);
    mAutoParamDataSource.setProjMatrix (projMatrix);

    renderer->updateAutoUniform(mAutoDataSource);
    renderer->updateCustUniform ();

    renderer->setTexture(mat->getTexture());

   
    renderer->_render(ro);
    
    renderer->endFrame();
}




void World::startRendering ()
{

    for (entity[i]) {
        entity[i]->getRenderOperation (ro);
        mat = entity[i]->getMaterial ();
        worldMatrix = entity[i]->getWorldMatrix ();
        mCamera.getViewMatrix (viewMatrix);
        mCamera.getProjMatrix (projMatrix);

        renderOneObject (ro, mat, worldMatrix, viewMatrix, projMatrix);
    }

}

```


# renderer #

```

class Renderer
{

    mCurrentShaderProgram;


    void bindShaderProgram (*prog);
    void updateAutoUniform(AutoDataSource *auto);
    void updateCustUniform ();

   

}


void Renderer::setTexture(tex)
{

    if (text) {

        glEnable(GL_TEXTURE_2D);
        glActiveTexture （unit）；
        glBindTexture (GL_TEXTURE_2D, tex->getTextureID());
    }

}

void Renderer::bindShaderProgram (*prog)
{
    mCurrentShaderProgram=prog;
    prog->useProgram();
}




void Renderer::updateAutoUniform(mAutoDataSource)
{
    mCurrentProgram->updateAutoUniform (auto);
}


void Renderer::updateCustUniform()
{
    mCurrentProgram->updateCustUniform ();
}


```


# ShaderProgramParameters #


```

class ShaderProgramParameters 
{

public:

    void setNamedAttrConstant (AttrConstantType type, char *name);
    void setNamedAutoUniformConstant ( AutoUniformConstantType type, char *name );
    void setNamedCustUniformConstant ( CustUniformConstantType type, char *name );



    updateAutoUniformConst (AutoParamDataSource* source);
    updateCustUniformConst ();
  

}

```



# ShaderProgram #


```

class ShaderProgram
{

public:

    void bindShaderParameters (*params);
    void bindProgramParameters (ShaderProgramParameters *params);

    void loadSource();
    void loadBinary ();

private:
    ShaderProgramParameters *params;

 
    
}


void ShaderProgram::updateAuto(auto)
{
}



void ShaderProgram::bindProgramParameters (*params)
{


void ShaderProgram::bindShaderParameters (ShaderProgramParams* params)
{
    mParameters = params;

    glGetUniformLocation();
    glGetAttribLoacation();

    write index to list 

}

    

}


```

# Texture #

```
Class Texture
{
    unit_id
    tex_id;
    
}

```

# 用户使用 #

```

World *world;
Camera *camera;
ShaderProgram *prog;
Material *mat;



void init ()
{

    world = new World();
    world->setSize (w, h);
    world->setBackColor (r, g, b, a);

    camera= world->createCamera ("name");

    prg = new ShaderProgram ();
    prg->loadShaderSource (vert_file,frag_file);
 
    params = new ShaderProgramParams ();

    //auto uniform
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "prj_matrx");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_matrx");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_matrx");

    //custom uniform
    params->setNamedCustConstant (type, "sample2d", int);

    //attribution
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX_INDEX, "vPosition");

    shaderProgram->setShaderParameters (params);


    //create Material
    mat = new Material ();
    mat->setShaderProgram (shaderProgram);
    //maybe mat->setTexture (tex); 

    //create mesh
    mesh = new Mesh ();
    mesh->setVertices (vertices, count);
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);
    

    Entity* entity = world->createEntity();
    entity->setMesh (mesh);
    entity->setMaterial (mat);
    
}

void display ()
{

    world->startRendering();

    swap();

}

void destroy ()
{

    delete params;
    delete shaderProgram;

    delete mat;
    

    //delete camera    
    world->destroyCameras();

    //delete entity
    world->destroyEntities();

    delete world;

}

```


Add your content here.  Format your content with:
  * Text in **bold** or _italic_
  * Headings, paragraphs, and lists
  * Automatic links to other wiki pages