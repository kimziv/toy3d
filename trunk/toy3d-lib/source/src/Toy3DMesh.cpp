
#include "Toy3DMesh.h"
#include "Toy3DMath.h"


TOY3D_BEGIN_NAMESPACE

    Mesh::Mesh() 
    {
        mVertices = NULL;
        mColors = NULL;
        mUVs = NULL;
        mNormals = NULL;
        mVertexCount = 0;
    }

    Mesh::~Mesh() 
    {
        FREEANDNULL(mVertices);
        FREEANDNULL(mColors);
        FREEANDNULL(mUVs);
        FREEANDNULL(mNormals);

        mVertexCount = 0;
    }

    void Mesh::setVertices (Real* pVertices, Uint count)
    {
        Uint size;

        if( !pVertices )
        {
            TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
            return;
        }

        FREEANDNULL(mVertices);
        mVertexCount = count;

        size = count * 3 * sizeof(Real);
        mVertices = (Real*)malloc(size);
        memcpy (mVertices, pVertices, size);

       return;
    }

    void Mesh::setColors (Real* pColors, Uint count)
    {
        Uint size;

        if( !pColors )
        {
            TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
            return;
        }

        FREEANDNULL(mColors);

        if(mVertexCount==0)
        {
            mVertexCount = count;
        }
        else if(mVertexCount!=count)
        {
            TOY3D_TIPS("Error: colors' count doesn't agree with existing data.");
            return;
        }

        size = mVertexCount * 4 * sizeof(Real);
        mUVs = (Real*)malloc(size);
        memcpy (mColors, pColors, size);
        
        return;
    }

    void Mesh::setUVs(Real* pUVs, Uint count)
    {
        Uint size;

        if( !pUVs )
        {
            TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
            return;
        }

        FREEANDNULL(mUVs);
        
        if(mVertexCount==0)
        {
            mVertexCount = count;
        }
        else if(mVertexCount!=count)
        {
            TOY3D_TIPS("Error: uvs' count doesn't agree with existing data.");
            return;
        }
        
        size = mVertexCount * 2 * sizeof(Real);
        mUVs = (Real*)malloc(size);
        memcpy (mUVs, pUVs, size);
        
        return;
    }

    void Mesh::setNormals(Real* pNormals, Uint count)
    {
        Uint size;

        if( !pNormals )
        {
            TOY3D_PRINT("NULL POINTER.", __FILE__, __LINE__);
            return;
        }

        FREEANDNULL(mNormals);

        if(mVertexCount==0)
        {
            mVertexCount = count;
        }
        else if(mVertexCount!=count)
        {
            TOY3D_TIPS("Error: normals' count doesn't agree with existing data.");
            return;
        }

        size = mVertexCount * 3 * sizeof(Real);
        mUVs = (Real*)malloc(size);
        memcpy(mNormals, pNormals, size);

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
                ro->setColors( mColors );
            }

            if( mUVs )
            {
                ro->setUVs( mUVs );
            }

            if(mNormals)
            {
                ro->setNormals(mNormals);
            }
        }
    }



TOY3D_END_NAMESPACE
