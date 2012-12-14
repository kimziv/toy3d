
#include "Toy3DMesh.h"
#include "Toy3DMath.h"


TOY3D_BEGIN_NAMESPACE

    Mesh::Mesh() 
    {
        mVertices = NULL;
        MvGl2DemoMatrixIdentity( mModelMatrix );
    }


    Mesh::~Mesh() 
    {
        if( mVertices )
            FREEANDNULL(mVertices);
    }

    void Mesh::setVertices (Real* vertices, Uint count)
    {
       if (mVertices) 
           FREEANDNULL (mVertices);

       mVertexCount = count;
       Uint size = count * 3 * sizeof (Real);
       mVertices = (Real*)malloc(size);
       memcpy (mVertices, vertices, size);
    }

    void Mesh::setRenderMode (RenderMode mode) 
    {
        mRenderMode = mode;
    }

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

    void Mesh::getRenderOperation(RenderOperation* ro)
    {
        if (ro) {
            ro->setVertex( mVertices, mVertexCount);
            ro->setRenderMode( mRenderMode );
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
        
    }


    void Mesh::rotate (Real x, Real y, Real z)
    {


        MvGl2DemoMatrixRotate(mModelMatrix, x, 1.0f, 0.0f, 0.0f);
        MvGl2DemoMatrixRotate(mModelMatrix, y, 0.0f, 1.0f, 0.0f);
        MvGl2DemoMatrixRotate(mModelMatrix, z, 0.0f, 0.0f, 1.0f);

    }



TOY3D_END_NAMESPACE
