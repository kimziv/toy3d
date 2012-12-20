
#include "Toy3DMesh.h"
#include "Toy3DMath.h"


TOY3D_BEGIN_NAMESPACE

    Mesh::Mesh() 
    {
        mVertices = NULL;
        mColors = NULL;
        mUVs = NULL;
        mNormals = NULL;
        MvGl2DemoMatrixIdentity( mModelMatrix );
    }


    Mesh::~Mesh() 
    {
        FREEANDNULL(mVertices);
        FREEANDNULL(mColors);
        FREEANDNULL(mUVs);
        FREEANDNULL(mNormals);
    }

    void Mesh::setVertices (Real* vertices, Uint count)
    {
       FREEANDNULL(mVertices);

       mVertexCount = count;
       Uint size = count * 3 * sizeof(Real);
       mVertices = (Real*)malloc(size);
       memcpy (mVertices, vertices, size);

       return;
    }

    void Mesh::setUVs(Real* uvs, Uint count)
    {
        FREEANDNULL(mUVs);

        Uint size = mVertexCount * 2 * sizeof(Real);
        mUVs = (Real*)malloc(size);
        memcpy (mUVs, uvs, size);

        return;
    }

    void Mesh::setRenderMode (RenderMode mode) 
    {
        mRenderMode = mode;
    }

    void Mesh::setTextureID( Uint id )
    {
        mTextureID = id;
        return;
    }
/*
    RenderMode Mesh::getRenderMode ()
    {
        return mRenderMode;
    }

    Real* Mesh::getVertices()
    {
        return mVertices;
    }

    Uint Mesh::getVerticesCount()
    {
        return mVertexCount;
    }
*/
    void Mesh::getRenderOperation(RenderOperation* ro)
    {
        if (ro) {
            ro->setVertices( mVertices, mVertexCount);
            ro->setRenderMode( mRenderMode );

            /*
            if( mColors )
            {
                ro->setColors( mColors, mVertexCount );
            }
            */

            if( mUVs )
            {
                ro->setUVs( mUVs, mVertexCount );
                if( mTextureID )
                    ro->setTextureID( mTextureID );
            }
        }
    }


    void Mesh::getModelMatrix (Real matrix[MATRIX_4x4_SIZE])
    {
        memcpy( matrix, mModelMatrix, MATRIX_4x4_SIZE*sizeof(Real) );
        return ;
    }


    void Mesh::translate (Real x, Real y, Real z)
    {
        
        MvGl2DemoMatrixTranslate(mModelMatrix, x, y, z);
        return;
    }


    void Mesh::rotate (Real x, Real y, Real z)
    {
        MvGl2DemoMatrixRotate(mModelMatrix, x, 1.0f, 0.0f, 0.0f);
        MvGl2DemoMatrixRotate(mModelMatrix, y, 0.0f, 1.0f, 0.0f);
        MvGl2DemoMatrixRotate(mModelMatrix, z, 0.0f, 0.0f, 1.0f);

        return;
    }



TOY3D_END_NAMESPACE
