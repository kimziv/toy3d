
#ifndef _TOY3D_WORLD_H
#define _TOY3D_WORLD_H

#include "Toy3DCommon.h"
#include "Toy3DCamera.h"
#include "Toy3DEntity.h"
#include "Toy3DRenderer.h"
#include "Toy3DAutoParamDataSource.h"
#include "Toy3DFrameListener.h"


TOY3D_BEGIN_NAMESPACE

	class World 
    {
	private:

        Uint mWidth;
        Uint mHeight;

        Real mBackColorRed;
        Real mBackColorGreen;
        Real mBackColorBlue;
        Real mBackColorAlpha;

        Entity *mEntities[MAX_ENTITY_COUNT];
        Uint mEntityCount;

        Camera*             mCamera;
//        ShaderProgram       *mShaderProgram;
        AutoParamDataSource mAutoParamDataSource;

        Real mWorldMatrix[MATRIX_4x4_SIZE];

    public:

		World();
        ~World();

        Entity* createEntity();
        void destroyAllEntities();
        //Mesh* createMeshByFile( const char* fileName );
        Camera* createCamera( const char *name );
        Renderer* createRenderer();


        void renderOneObject (RenderOperation *ro, Material *mat, 
            Real worldMatrix[16], Real viewMatrix[16], Real projMatrix[16]);      
  
        void startRendering ();

        void setSize( Uint width, Uint height );
        void setBackColor( Real r, Real g, Real b, Real a);
        void resize( Uint width, Uint height );
        void setWorldDepth( Uint flag, Uint funcMode );
        void setWorldBlend( Uint flag, Uint srcMode, Uint dstMode );

        void rotate (Real x, Real y, Real z);


        void renderScene (Camera* camera, Viewport *vp);

        //Shoud be in root class
    private:        
        Renderer   mRenderer;
        TPtrArray  mFrameListeners; 

        Bool fireFrameStarted();
        Bool fireFrameEnded();


    public:
        void renderOneFrame ();
        RenderWindow* createRenderWindow();
        RenderTexture* createRenderTexture(Texture *tex);

        void addFrameListener (FrameListener *newListener);
        void removeFrameListener (FrameListener *oldListener);
     
        


	};


TOY3D_END_NAMESPACE

#endif
