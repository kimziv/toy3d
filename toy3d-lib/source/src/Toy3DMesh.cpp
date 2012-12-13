
#include "Toy3DMesh.h"


TOY3D_BEGIN_NAMESPACE

    Mesh::Mesh() 
    {

        mVertices = NULL;
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




TOY3D_END_NAMESPACE
