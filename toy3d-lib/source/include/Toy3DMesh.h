
#ifndef _TOY3D_MESH_H
#define _TOY3D_MESH_H

#include "Toy3DCommon.h"
#include "Toy3DRenderOperation.h"


TOY3D_BEGIN_NAMESPACE


    class Mesh 
    {

    private:
        RenderMode mRenderMode;
        Real *mVertices;
        Real* mColors;
        Real* mUVs;
        Real* mNormals;

        Uint mVertexCount;


    public:
        Mesh();
        ~Mesh();

    public:

        void setRenderMode (RenderMode mode);
        void setVertices (Real* pVeritces, Uint count);
        void setColors (Real* pColors, Uint count);
        void setUVs (Real* pUVs, Uint count);
        void setNormals(Real* pNormals, Uint count);

        void getRenderOperation(RenderOperation* ro);

    };



TOY3D_END_NAMESPACE

#endif
