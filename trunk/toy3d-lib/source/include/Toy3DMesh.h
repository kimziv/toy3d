
#ifndef _TOY3D_MESH_H
#define _TOY3D_MESH_H

#include "Toy3DCommon.h"


TOY3D_BEGIN_NAMESPACE


     enum RenderMode {
        TOY3D_POINTS = 1,
        TOY3D_LINES = 2,
        TOY3D_LINE_STRIP = 3,
        TOY3D_TRIANGLES = 4,
        TOY3D_TRIANGLE_STRIP = 5,
        TOY3D_TRIANGLE_FAN = 6
     };


    class Mesh 
    {

    private:
        RenderMode mRenderMode;
        Real *mVertices;


    public:
        Mesh();
        ~Mesh();

    public:
        void setVertices (Real* veritces, Uint count);
        void setRenderMode (RenderMode mode);


    };



TOY3D_END_NAMESPACE

#endif
