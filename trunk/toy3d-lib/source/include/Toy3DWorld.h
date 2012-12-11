
#ifndef _TOY3D_WORLD_H
#define _TOY3D_WORLD_H

#include "Toy3DCommon.h"
#include "Toy3DCamera.h"
#include "Toy3DMesh.h"
#include "Toy3DRenderer.h"
#include "Toy3DShaderProgram.h"
#include "Toy3DAutoParamDataSource.h"


TOY3D_BEGIN_NAMESPACE

    enum ShaderType
    {
        SHADER_SOURCE,
        SHADER_BINARY
    };

	class World 
    {
	private:

        int     mWidth;
        int     mHeight;

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
        Camera* createCamera( Uchar *name );
        ShaderProgram* createShaderProgram( ShaderType type,
            Uchar *vert, Uint vertLength, Uchar *frag, Uint fragLength );
        Renderer* createRenderer();

        void setMesh();
        void setShaderProgram();

        void startRendering ();

        void setSize( Uint width, Uint height );
        void setWorldDepth( Uint flag, Uint funcMode );
        void setWorldBlend( Uint flag, Uint srcMode, Uint dstMode );
        void setWorldBkgColor( Real r, Real g, Real b, Real a);
	};


TOY3D_END_NAMESPACE

#endif
