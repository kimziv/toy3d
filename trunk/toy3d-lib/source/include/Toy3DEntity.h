
#ifndef _TOY3D_ENTITY_H
#define _TOY3D_ENTITY_H

#include "Toy3DCommon.h"
#include "Toy3DMesh.h"
#include "Toy3DMaterial.h"
#include "Toy3DRenderOperation.h"


TOY3D_BEGIN_NAMESPACE


    class Entity 
    {

    private:
        Mesh* mMesh;
        Material* mMaterial;
        ShaderProgram* mShaderProgram;
        Bool mVisible;

        Real mModelMatrix[MATRIX_4x4_SIZE]; 


    public:
        Entity();
        ~Entity();

    public:
        void rotate (Real x, Real y, Real z);
        void translate (Real x, Real y, Real z);

        //Mesh* createMesh ();
        //void destroyMesh ();
        void setMesh(Mesh *mesh);
        void setMaterial (Material *mat);
        Material *getMaterial ();

        void getRenderOperation(RenderOperation* ro);
        void getModelMatrix (Real matrix[MATRIX_4x4_SIZE]);

        void setVisible(Bool visible);
        Bool isVisible();


    };



TOY3D_END_NAMESPACE

#endif
