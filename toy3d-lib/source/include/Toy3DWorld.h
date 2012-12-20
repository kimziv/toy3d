
#ifndef _TOY3D_WORLD_H
#define _TOY3D_WORLD_H

#include "Toy3DCommon.h"
#include "Toy3DCamera.h"
#include "Toy3DMesh.h"
#include "Toy3DRenderer.h"
#include "Toy3DShaderProgram.h"
#include "Toy3DAutoParamDataSource.h"


TOY3D_BEGIN_NAMESPACE

	class World 
    {
	private:

        Uint     mWidth;
        Uint     mHeight;

        Real mBackColorRed;
        Real mBackColorGreen;
        Real mBackColorBlue;
        Real mBackColorAlpha;

        Uint   mMeshCount;

        Camera              mCamera;
        Mesh                *mMeshes[MAX_MESH_COUNT];
        ShaderProgram       *mShaderProgram;
        AutoParamDataSource mAutoParamDataSource;
        Renderer            *mRenderer;

        Real mWorldMatrix[MATRIX_4x4_SIZE];

    public:

		World();
        ~World();

        Mesh* createMesh();
        //Mesh* createMeshByFile( const char* fileName );
        Camera* createCamera( const char *name );
        ShaderProgram* createShaderProgram();
        Renderer* createRenderer();

        //void setMesh();

        void startRendering ();

        void setSize( Uint width, Uint height );
        void setBackColor( Real r, Real g, Real b, Real a);
        void resize( Uint width, Uint height );
        void setWorldDepth( Uint flag, Uint funcMode );
        void setWorldBlend( Uint flag, Uint srcMode, Uint dstMode );

        void rotate (Real x, Real y, Real z);
	};


TOY3D_END_NAMESPACE

#endif
