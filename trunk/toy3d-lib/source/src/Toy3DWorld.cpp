

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
        Mesh *temp;
        while( mMeshCount )
        {
            temp = mMeshes[--mMeshCount];
            mMeshes[mMeshCount] = 0;
            delete temp;
        }

        DELETEANDNULL( mShaderProgram );
        //DELETEANDNULL( mRenderer );//now mRenderer is an object not pointer
    }

    void World::startRendering ()
    {
        Real matrix[MATRIX_4x4_SIZE];
        Real mesh_matrix[MATRIX_4x4_SIZE];
        RenderOperation *ro = NULL;
        Uint index;

        //set AutoParamDataSource 
        //Fixme: where is world matrix value 
//        mAutoParamDataSource.setWorldMatrix ( mWorldMatrix );
        mCamera.getViewMatrix( matrix );
        mAutoParamDataSource.setViewMatrix ( matrix );
        mCamera.getProjectionMatrix( matrix );
        mAutoParamDataSource.setProjectionMatrix( matrix ); 

        ro = new RenderOperation ();

        index = mShaderProgram->getShaderParameters()->getAttrConstIndex (TOY3D_ATTR_VERTEX_INDEX);
        ro->setShaderAttribution (TOY3D_ATTR_VERTEX_INDEX, index);

        //need to fix wether there is texture
        //UV
        index = mShaderProgram->getShaderParameters()->getAttrConstIndex (TOY3D_ATTR_UV_INDEX);
        ro->setShaderAttribution (TOY3D_ATTR_UV_INDEX, index);


        mRenderer.setViewPort (0.0, 0.0, mWidth, mHeight);
        mRenderer.beginFrame ();
        mRenderer.setBackColor (mBackColorRed, mBackColorGreen, mBackColorBlue, mBackColorAlpha);

        for (Uint i = 0; i < mMeshCount; i++)
        {
            mMeshes[i]->getRenderOperation(ro);

            mMeshes[i]->getModelMatrix (mesh_matrix);
            MvGl2DemoMatrixCopy (matrix, mWorldMatrix);
            MvGl2DemoMatrixMultiply (matrix, mesh_matrix);
            //mMeshes[i]->getModelMatrix (matrix);
            mAutoParamDataSource.setWorldMatrix ( matrix );
            mAutoParamDataSource.setTextureUnit( ro->getTextureID() );

            //update auto shader paramters
            mShaderProgram->getShaderParameters()->updateAutoConstParams (&mAutoParamDataSource); 

            mRenderer.useShaderProgram(mShaderProgram->getShaderProgramID());
            mRenderer.render(ro);
        }

        mRenderer.endFrame ();
     
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
/*
    void World::setMesh ()
    {
        printf ("Set mesh...\n");
    }
*/

    void World::setSize( Uint width, Uint height )
    {
        mWidth = width;
        mHeight = height;

        return;
    }
/*
    void World::setWorldDepth( Uint flag, Uint funcMode )
    {
        mRenderer.setDepthTest(flag, funcMode);
        return;
    }

    void World::setWorldBlend( Uint flag, Uint srcMode, Uint dstMode )
    {
        return;
    }
*/
    void World::setBackColor( Real r, Real g, Real b, Real a)
    {

        mBackColorRed = r;
        mBackColorGreen = g;
        mBackColorBlue = b;
        mBackColorAlpha = a;

    }

    void World::resize( Uint width, Uint height )
    {
        setSize( width, height );
        return;
    }
    


    void World::rotate (Real x, Real y, Real z)
    {
        MvGl2DemoMatrixIdentity(mWorldMatrix);
        MvGl2DemoMatrixRotate(mWorldMatrix, x, 1.0f, 0.0f, 0.0f);
        MvGl2DemoMatrixRotate(mWorldMatrix, y, 0.0f, 1.0f, 0.0f);
        MvGl2DemoMatrixRotate(mWorldMatrix, z, 0.0f, 0.0f, 1.0f);
      
        return;
    }


TOY3D_END_NAMESPACE
