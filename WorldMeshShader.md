# sample code #

画四边形 rectangle.


```

#define WINDOW_W   800
#define WINDOW_H   480


Real vertices[18] = {
   1.0, 1.0, 1.0,
   ...
   ...
};

#define VERTEX_COUNT 6


World *world = NULL;




void init ()
{

   world = new World ();


   //camera...
   Camera *camera = world->createCamera ("camera1");
   camera->lookAt (0.0, 0,0, 1.0, 0.0, 0,0, 0.0, 0.0, 1.0, 0.0);
   camera->perspective (45.0, WINDOW_W/WINDOW_H, 1.0, 1000.0);



   //shader...

   ShaderProgram *shaderProgram = world->createShaderProgram();
   shaderProgram->loadShaderSource ("rect.vert", "rect.frag");

   ShaderProgramParameters *params = new ShaderProgramParameters ();
   paras->setNamedAutoConstant ("projMat", AutoConstantType::TOY3D_ACT_PROJECTION_MATRIX);

   params->setNamedAutoConstant ("viewMat",AutoConstantType::TOY3D_ACT_VIEW_MATRIX);

   params->setNamedAutoConstant ("worldMat",AutoConstantType::TOY3D_ACT_WORLD_MATRIX);
   
    
   shaderProgram->bindShaderParameters(params);


   //mesh...
   Mesh *mesh = world->createMesh ();
   mesh->setVertices (vertices, VERTEX_COUNT);
   
}

void draw ()
{

    world->startRendering();
}


int main ()
{
    glutInit();
}


```


# Common #

```

typedef float Real;
typedef unsigned char Uchar;
typedef unsigned short Ushort;
typedef unsigned int Uint;
typedef unsigned long Ulong;

typedef signed int Sint;



```

# World #

```

#define MAX_MESH_COUNT  8

class World 
{
    Camera mCamera;

    Mesh* mMeshes[MAX_MESH_COUNT];
    Uint mMeshCount;

    Mesh *createMesh ();
    void startRendering();
};

Mesh* World::createMesh ()
{
    //FIXME:  Maybe need search current mesh array to see if it already exist.

    Mesh *mesh = new Mesh();
    mMeshes[mMeshCount++] = mesh;

    return mesh;
}


Camera* World::createCamera (char *name)
{
    //FIXME:  need multiple cameras

    return &mCamera;
}



void World::startRendering ()
{
   //set AutoParamDataSource
   
   mAutoParamDataSource.setWorldMatrix (); //Fixme: where is world matrix value
   mAutoParamDataSource.setViewMatrix (mCamera.getViewMatrix());
   mAutoParamDataSource.setProjectionMatrix(mCamera.getProjectionMatrix());

   
   //update auto shader paramters
   mShaderProgram->getParameters()->updateAutoConstParams (&mAutoParamDataSource);
    


    for (int i = 0; i < mMeshCount; i++){
        mRenderer.render(mMeshes[i]);
    }



    
}

```


# Mesh #

```

class Mesh 
{
private:

    Real *mVertices;

public:
    Mesh();
    ~Mesh()

    void setVertices (Real* vertices, Uint count);
 
};

//count: vertex count
void Mesh::setVertices (Real* vertices, Uint count)
{
    if (mVertices)
        free (mVertices);

    mVertices = (Real*)malloc (count * 3 * sizeof (Real));
    memcpy (mVertices, vertices);
    
}



```

# Shader Program #


```

enum AutoConstantType
{
   TOY3D_ACT_WORLD_MATRIX,
   TOY3D_ACT_VIEW_MATRIX,
   TOY3D_ACT_PROJECTION_MATRIX, 
}




class ShaderProgramParams 
{
    AutoConstEntry* mAutoConstEntries[MAX_ENTRY_COUNT];
    Uint mEntryCount;

    ShaderProgramParams ();
    ~ShaderProgramParams ();
 
    void setAutoConsValue( Uint index, Real value[16] );
    void updateAutoConstParams (AutoParamDataSource *source);
    void setNamedAutoConstant (AutoConstType type, char *name);

}

ShaderProgramParams::ShaderProgramParams()
{
    mEntryCount = 0;
}

void ShaderProgramParams::updateAutoConstParams (AutoParamDataSource *source)
{
    int i;
    for ( i=0; i<mEntryCount; i++ )
    {
        switch( mAutoConstEntries[i]->type )
        {
        case TOY3D_ACT_WORLD_MATRIX:
            setAutoConstValue( mAutoConstEntries[i]->index, source->getWorldMatrix() );
            break;

        case TOY3D_ACT_VIEW_MATRIX:
            break;

        case TOY3D_ACT_PROJECTION_MATRIX:
            break;

        default:
            break;
        }
    }
    return;
}

void ShaderProgramParams::setNamedAutoConstant (AutoConstType type, char *name)
{

    isExist = find(name);

    if (!isExist) {

        index = glGetIndexXXXXX(name);

        AutoConstEntry *entry = new AutoConstEntry (type, name, index);
        mAutoConstEntries[mEntryCount++];
    }
}

void ShaderProgramParams::setAutoConsValue( Uint index, Real value[16]);
{
    //glUniformMatrix4fv(index, 1, 0, value);
}

```

Add your content here.  Format your content with:
  * Text in **bold** or _italic_
  * Headings, paragraphs, and lists
  * Automatic links to other wiki pages