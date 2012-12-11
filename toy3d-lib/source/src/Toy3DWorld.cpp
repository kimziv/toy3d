

#include "Toy3DWorld.h"
#include "Toy3DMath.h"

TOY3D_BEGIN_NAMESPACE

    World::World()
    {
        mMeshCount = 0;
        MvGl2DemoMatrixIdentity( mWorldMatrix );
    }

    World::~World() 
    {
        while( mMeshCount )
        {
            FREEANDNULL( mMeshes[--mMeshCount] );
        }
    }

    void World::startRendering ()
    {
        Real matrix[MATRIX_4x4_SIZE];

        printf ("Start rendering...\n");

        //set AutoParamDataSource 
        //Fixme: where is world matrix value 
        mAutoParamDataSource.setWorldMatrix ( mWorldMatrix );
        mCamera.getViewMatrix( matrix );
        mAutoParamDataSource.setViewMatrix ( matrix );
        mCamera.getProjectionMatrix( matrix );
        mAutoParamDataSource.setProjectionMatrix( matrix ); 

        //update auto shader paramters 
        mShaderProgram->getShaderParameters()->updateAutoConstParams (&mAutoParamDataSource); 

        //world矩阵应该与mesh矩阵运算
        for (int i = 0; i < mMeshCount; i++)
        {
            mRenderer->render(mMeshes[i]); 
        }

        return;
    }


    Mesh* World::createMesh () 
    { 
        //FIXME:  Maybe need search current mesh array to see if it already exist. 
        Mesh *mesh = new Mesh();
        mMeshes[mMeshCount++] = mesh;

        return mesh;
    } 

    Camera* World::createCamera (Uchar *name) 
    { 
        //FIXME:  need multiple cameras 
        
        return &mCamera; 
    } 

    ShaderProgram* World::createShaderProgram( ShaderType type,
            Uchar *vert, Uint vertLength, Uchar *frag, Uint fragLength )
    {
        //FIXME:  Maybe need to record which shader  is in use.
        mShaderProgram = new ShaderProgram();

        //WARNING:加载失败的情况未处理

        if( SHADER_SOURCE==type )
        {
            mShaderProgram->loadShaderSource( vert, frag);
        }
        else
        {
            mShaderProgram->loadShaerBinary( vert, vertLength, frag, fragLength );
        }

        return mShaderProgram;
    }

    Renderer* World::createRenderer()
    {
        return 0;
    }

    void World::setMesh ()
    {
        printf ("Set mesh...\n");
    }

    void World::setShaderProgram()
    {
        printf ("Set shader...\n");

        if( mShaderProgram )
            glUseProgram( mShaderProgram->getShaderProgramID() );
    }

    void World::setSize( Uint width, Uint height )
    {
        return;
    }

    void World::setWorldDepth( Uint flag, Uint funcMode )
    {
        return;
    }

    void World::setWorldBlend( Uint flag, Uint srcMode, Uint dstMode )
    {
        return;
    }

    void World::setWorldBkgColor( Real r, Real g, Real b, Real a)
    {
        mRenderer->setBackgroundColor( r, g, b, a );
    }
    

TOY3D_END_NAMESPACE
