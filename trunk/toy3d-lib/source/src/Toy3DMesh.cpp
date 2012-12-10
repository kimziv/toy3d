
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

       Uint size = count * 3 * sizeof (Real);
       mVertices = (Real*)malloc(size);
       memcpy (mVertices, vertices, size);
    
    }

    void Mesh::setRenderMode (RenderMode mode) 
    {
        mRenderMode = mode;
    }




TOY3D_END_NAMESPACE
