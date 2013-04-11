

#include "Toy3DWorld.h"
#include "Toy3DTextureUnitState.h"
#include "Toy3DMath.h"


TOY3D_BEGIN_NAMESPACE

    World::World()
    {
        mEntityCount = 0;
        MvGl2DemoMatrixIdentity( mWorldMatrix );

        mCamera = NULL;

        mFrameListeners.create();

    }

    World::~World()
    {
        if (mCamera)
            delete mCamera;

        mFrameListeners.destroy();
    }

    void World::renderOneObject (RenderOperation *ro, Material *mat, 
            Real worldMatrix[16], Real viewMatrix[16], Real projMatrix[16])      
    {
        Uint i, count = 0;
        TextureUnitState *texUnits = NULL;

        mRenderer.bindShaderProgram(mat->getShaderProgram());
       
        mAutoParamDataSource.setWorldMatrix (worldMatrix); 
        mAutoParamDataSource.setViewMatrix (viewMatrix); 
        mAutoParamDataSource.setProjectionMatrix (projMatrix); 
        //mRenderer.setTexture(mat->getTexture());

        mRenderer.updateAutoUniform (&mAutoParamDataSource);
        mRenderer.updateCustUniform ();

        if(mat->hasAlphaBlending())
        {
            mRenderer.enableBlending(TRUE);
            //mRenderer.setSceneBlending(mat->getBlendingOp());
            mRenderer.setSceneBlending(
                mat->getSrcBlendFactor(),mat->getDestBlendFactor(), mat->getBlendMode());
        }

        count = mat->getTextureUnitStateSize();
        for(i=0; i<count; i++)
        {
            texUnits = mat->getTextureUnitStates(i);
            mRenderer.setTextureUnitSettings(texUnits);
        }

        mRenderer.render (ro);

        if(mat->hasAlphaBlending())
        {
            mRenderer.enableBlending(FALSE);
        }

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

        mRenderer.setViewPort (0,0, mWidth, mHeight);
        mRenderer.beginFrame();
        mRenderer.setBackColor (mBackColorRed, mBackColorGreen, mBackColorBlue, mBackColorAlpha);

        for (i = 0; i < mEntityCount; i++) {


            if (mEntities[i]->isVisible() == FALSE)
                continue;

            ro = new RenderOperation ();

            mEntities[i]->getRenderOperation (ro);

            mat = mEntities[i]->getMaterial();

            mEntities[i]->getModelMatrix (entityMatrix);
            MvGl2DemoMatrixCopy (worldMatrix, mWorldMatrix);
            MvGl2DemoMatrixMultiply (worldMatrix, entityMatrix);

            if (mCamera) {
                mCamera->getViewMatrix(viewMatrix);
                mCamera->getProjectionMatrix(projMatrix);
            }

            renderOneObject (ro, mat, worldMatrix, viewMatrix, projMatrix);

            delete ro;
        }

        mRenderer.endFrame();

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
        
        mCamera = new Camera (this);
        return mCamera; 
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

    void World::renderScene (Camera *camera, Viewport *vp)
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

        mRenderer.setViewport (vp);
        //mRenderer.setViewPort (0,0, mWidth, mHeight);

        mRenderer.beginFrame();
        mRenderer.setBackColor (mBackColorRed, mBackColorGreen, mBackColorBlue, mBackColorAlpha);

        for (i = 0; i < mEntityCount; i++) {

            if (mEntities[i]->isVisible() == FALSE)
                continue;

            ro = new RenderOperation ();

            mEntities[i]->getRenderOperation (ro);

            mat = mEntities[i]->getMaterial();

            mEntities[i]->getModelMatrix (entityMatrix);
            MvGl2DemoMatrixCopy (worldMatrix, mWorldMatrix);
            MvGl2DemoMatrixMultiply (worldMatrix, entityMatrix);

            if (camera) {
                camera->getViewMatrix(viewMatrix);
                camera->getProjectionMatrix(projMatrix);
            }

            renderOneObject (ro, mat, worldMatrix, viewMatrix, projMatrix);

            delete ro;
        }

        mRenderer.endFrame();

    }

    void World::renderOneFrame ()
    {

        if(fireFrameStarted() == FALSE)
            return;

        mRenderer.updateAllRenderTargets ();

        fireFrameEnded();

        return;

    }

    RenderWindow* World::createRenderWindow ()
    {
        RenderWindow *win = NULL;

        win = mRenderer.createRenderWindow();

        return win;
    }

    RenderTexture* World::createRenderTexture(Texture *tex)
    {
        RenderTexture *rt = NULL;

        rt = mRenderer.createRenderTexture(tex);
        return rt;
    }


    Bool World::fireFrameStarted()
    {
        Uint length = mFrameListeners.getLength();
        for (Uint i = 0; i < length; i++) {
            FrameListener *fl = (FrameListener*)mFrameListeners.getElement(i);
            if(fl->frameStarted() == FALSE)
                return FALSE;
        }

        return TRUE;
    }

    Bool World::fireFrameEnded()
    {
        Uint length = mFrameListeners.getLength();
        for (Uint i = 0; i < length; i++) {
            FrameListener *fl = (FrameListener*)mFrameListeners.getElement(i);
            if(fl->frameEnded() == FALSE)
                return FALSE;
        }

        return TRUE;

    }



    void World::addFrameListener (FrameListener *newListener)
    {
        mFrameListeners.append(newListener);
    }

    //NOTICE: only remove from array,  user free the pointer 
    void World::removeFrameListener (FrameListener *oldListener)
    {
        mFrameListeners.remove(oldListener);
    }



TOY3D_END_NAMESPACE
