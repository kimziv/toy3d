

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
        RenderOperation *ro = NULL;

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

        ro = new RenderOperation ();

        Uint index = mShaderProgram->getShaderParameters()->getAttrConstIndex (TOY3D_ATTR_VERTEX_INDEX);
        ro->setShaderAttribution (TOY3D_ATTR_VERTEX_INDEX, index);

        mRenderer->setViewPort (0.0, 0.0, mWidth, mHeight);
        mRenderer->beginFrame ();
        mRenderer->setBackColor (mBackColorRed, mBackColorGreen, mBackColorBlue, mBackColorAlpha);

        for (int i = 0; i < mMeshCount; i++)
        {
            mMeshes[i]->getRenderOperation(ro);

            //fixme: set shader attribution index 

            mRenderer->render(ro);
        }

        mRenderer->endFrame ();
     
        delete ro;

        return;
    }


    Mesh* World::createMesh () 
    { 
        //FIXME:  Maybe need search current mesh array to see if it already exist. 
        Mesh *mesh = new Mesh();
        mMeshes[mMeshCount++] = mesh;

        return mesh;
    } 

    Camera* World::createCamera (const char *name) 
    { 
        //FIXME:  need multiple cameras 
        
        return &mCamera; 
    } 

    ShaderProgram* World::createShaderProgram()
    {
        //FIXME:  Maybe need to record which shader  is in use.
        mShaderProgram = new ShaderProgram();

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
        mWidth = width;
        mHeight = height;

        return;
    }

    void World::setWorldDepth( Uint flag, Uint funcMode )
    {
        mRenderer->setDepthTest(flag, funcMode);
        return;
    }

    void World::setWorldBlend( Uint flag, Uint srcMode, Uint dstMode )
    {
        return;
    }

    void World::setBackColor( Real r, Real g, Real b, Real a)
    {

        mBackColorRed = r;
        mBackColorGreen = g;
        mBackColorBlue = b;
        mBackColorAlpha = a;

    }
    

TOY3D_END_NAMESPACE
