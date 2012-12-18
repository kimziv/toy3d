
#ifndef _TOY3D_MESH_H
#define _TOY3D_MESH_H

#include "Toy3DCommon.h"
#include "Toy3DRenderOperation.h"


TOY3D_BEGIN_NAMESPACE

/*
     enum RenderMode {
        TOY3D_POINTS = 1,
        TOY3D_LINES = 2,
        TOY3D_LINE_STRIP = 3,
        TOY3D_TRIANGLES = 4,
        TOY3D_TRIANGLE_STRIP = 5,
        TOY3D_TRIANGLE_FAN = 6
     };
*/

    class Mesh 
    {

    private:
        RenderMode mRenderMode;
        Real *mVertices;
        Real* mColors;
        Real* mUVs;
        Real* mNormals;

        Uint mVertexCount;
        Uint mTextureID;
        Real mModelMatrix[MATRIX_4x4_SIZE]; 


    public:
        Mesh();
        ~Mesh();

    public:
        void rotate (Real x, Real y, Real z);
        void translate (Real x, Real y, Real z);

        void setRenderMode (RenderMode mode);
        void setVertices (Real* veritces, Uint count);
        void setColors (Real* colors, Uint count);
        void setUVs (Real* uvs, Uint count);
        void setNormals(Real* normals, Uint count);
        void setTextureID( Uint id );

        void getModelMatrix (Real matrix[MATRIX_4x4_SIZE]);
        //RenderMode getRenderMode();
        //Real* getVertices();
        //Uint getVertexCount();
        void getRenderOperation(RenderOperation* ro);

    };



TOY3D_END_NAMESPACE

#endif
