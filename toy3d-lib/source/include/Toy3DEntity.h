
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
        Texture* mTexture;
        ShaderProgram* mShaderProgram;

        Real mModelMatrix[MATRIX_4x4_SIZE]; 


    public:
        Entity();
        ~Entity();

    public:
        void rotate (Real x, Real y, Real z);
        void translate (Real x, Real y, Real z);

        Mesh* createMesh ();
        void destroyMesh ();

        Material* createMaterial ();
        void destroyMaterial ();

        void setTexture( Texture* tex);

        void getRenderOperation(RenderOperation* ro);
        void getModelMatrix (Real matrix[MATRIX_4x4_SIZE]);

        Material *getMaterial ();

    };



TOY3D_END_NAMESPACE

#endif
