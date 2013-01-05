
#include "Toy3DMesh.h"
#include "Toy3DMath.h"


TOY3D_BEGIN_NAMESPACE

    Mesh::Mesh() 
    {
        mVertices = NULL;
        mColors = NULL;
        mUVs = NULL;
        mNormals = NULL;
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


    void Mesh::getRenderOperation(RenderOperation* ro)
    {
        if (ro) {
            ro->setRenderMode( mRenderMode );
            if(mVertices)
            {
                ro->setVertices( mVertices, mVertexCount);
            }

            if( mColors )
            {
                ro->setColors( mColors, mVertexCount );
            }

            if( mUVs )
            {
                ro->setUVs( mUVs, mVertexCount );
            }

            if(mNormals)
            {
                ro->setNormals(mNormals, mVertexCount);
            }
        }
    }



TOY3D_END_NAMESPACE
