

#include "Toy3DWorld.h"
#include "Toy3DMath.h"

TOY3D_BEGIN_NAMESPACE

    World::World()
    {
        mEntityCount = 0;
        MvGl2DemoMatrixIdentity( mWorldMatrix );
    }

    World::~World()
    {
    }



    void World::renderOneObject (RenderOperation *ro, Material *mat, 
            Real worldMatrix[16], Real viewMatrix[16], Real projMatrix[16])      
    {

        mRenderer.setViewPort (0,0, mWidth, mHeight);

        mRenderer.beginFrame();

        mRenderer.bindShaderProgram(mat->getShaderProgram());
       
        mAutoParamDataSource.setWorldMatrix (worldMatrix); 
        mAutoParamDataSource.setViewMatrix (viewMatrix); 
        mAutoParamDataSource.setProjectionMatrix (projMatrix); 
        mRenderer.setTexture(mat->getTexture());

        mRenderer.updateAutoUniform (&mAutoParamDataSource);
        mRenderer.updateCustUniform ();

        mRenderer.render (ro);

        mRenderer.endFrame();

        return;
    } 



    void World::startRendering ()
    {

        RenderOperation *ro = NULL;
        Uint i = 0;
        Material *mat = NULL;

        Real entityMatrix[MATRIX_4x4_SIZE];
 
        Real worldMatrix[MATRIX_4x4_SIZE]; 
        Real viewMatrix[MATRIX_4x4_SIZE]; 
        Real projMatrix[MATRIX_4x4_SIZE]; 

        if( mEntityCount == 0)
        {
            TOY3D_TIPS("At least create one Entity please.\n");
            return;
        }

        for (i = 0; i < mEntityCount; i++) {

            ro = new RenderOperation ();

            mEntities[i]->getRenderOperation (ro);

            mat = mEntities[i]->getMaterial();

            mEntities[i]->getModelMatrix (entityMatrix);
            MvGl2DemoMatrixCopy (worldMatrix, mWorldMatrix);
            MvGl2DemoMatrixMultiply (worldMatrix, entityMatrix);

            mCamera.getViewMatrix(viewMatrix);
            mCamera.getProjectionMatrix(projMatrix);

            renderOneObject (ro, mat, worldMatrix, viewMatrix, projMatrix);

            delete ro;
            
        }

    }
/*
    void World::startRendering ()
    {
        Real matrix[MATRIX_4x4_SIZE];
        Real mesh_matrix[MATRIX_4x4_SIZE];
        RenderOperation *ro = NULL;
        Uint index;

        //set AutoParamDataSource 
        mCamera.getViewMatrix( matrix );
        mAutoParamDataSource.setViewMatrix ( matrix );
        mCamera.getProjectionMatrix( matrix );
        mAutoParamDataSource.setProjectionMatrix( matrix ); 

        ro = new RenderOperation ();

        index = mShaderProgram->getAttrLocation(TOY3D_ATTR_VERTEX);
        ro->setShaderAttribution (TOY3D_ATTR_VERTEX, index);

        //need to fix wether there is texture
        //UV
        index = mShaderProgram->getAttrLocation(TOY3D_ATTR_UV);
        ro->setShaderAttribution (TOY3D_ATTR_UV, index);


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
            mAutoParamDataSource.setTextureUnit( ro->getTextureUnit() );

            //update auto shader paramters
            mShaderProgram->getShaderParameters()->updateAutoUniformConst (&mAutoParamDataSource); 
            //update custom shader paramters
            mShaderProgram->getShaderParameters()->updateCustUniformConst(); 

            mRenderer.useShaderProgram(mShaderProgram->getShaderProgramID());
            mRenderer.render(ro);
        }

        mRenderer.endFrame ();
     
        delete ro;

        return;
    }
*/

    Entity* World::createEntity () 
    { 
        //FIXME:  Maybe need search current mesh array to see if it already exist. 
        Entity *entity = new Entity();
        mEntities[mEntityCount++] = entity;

        return entity;
    } 

    void World::destroyAllEntities ()
    {
        Uint i = 0;
        Entity* entity = NULL;
        for (i = 0; i < mEntityCount; i++) {
            entity = mEntities[i];
            delete (entity);
        }
    }

    Camera* World::createCamera (const char *name) 
    { 
        //FIXME:  need multiple cameras 
        
        return &mCamera; 
    } 


/*
    ShaderProgram* World::createShaderProgram()
    {
        //FIXME:  Maybe need to record which shader  is in use.
        mShaderProgram = new ShaderProgram();

        return mShaderProgram;
    }
*/
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
