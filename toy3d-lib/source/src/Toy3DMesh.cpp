
#include "Toy3DMesh.h"


TOY3D_BEGIN_NAMESPACE

    Mesh::Mesh() 
    {

    }


    Mesh::~Mesh() 
    {
    }

    void Mesh::setVertices (Real* vertices, Uint count)
    {
       if (mVertices) 
           free (mVertices);

       mVerticesCount = count;
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

    Uint Mesh::getVerticesCount()
    {
        return mVerticesCount;
    }




TOY3D_END_NAMESPACE
