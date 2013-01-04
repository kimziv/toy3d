
#include "Toy3DEntity.h"
#include "Toy3DMath.h"


TOY3D_BEGIN_NAMESPACE

    Entity::Entity() 
    {
        mMesh = NULL;
        mMaterial = NULL;
        MvGl2DemoMatrixIdentity( mModelMatrix );
    }


    Entity::~Entity() 
    {
    }


    Mesh* Entity::createMesh ()
    {
        if (mMesh)
            delete mMesh;

        mMesh = new Mesh();

        return mMesh;
    }

    void Entity::destroyMesh ()
    {
        if (mMesh)
            delete mMesh;
    }


    Material* Entity::createMaterial ()
    {
        if (mMaterial)
            delete mMaterial;

        mMaterial = new Material ();

        return mMaterial;
        
    }

    void Entity::destroyMaterial ()
    {
        if (mMaterial)
            delete mMaterial;
    }



    void Entity::setTexture( Texture* tex)
    {
        mTexture = tex;
    }




    void Entity::getRenderOperation(RenderOperation* ro)
    {

        if (mMesh)
            mMesh->getRenderOperation(ro);

    }


    void Entity::getModelMatrix (Real matrix[MATRIX_4x4_SIZE])
    {
        memcpy( matrix, mModelMatrix, MATRIX_4x4_SIZE*sizeof(Real) );
        return ;
    }


    void Entity::translate (Real x, Real y, Real z)
    {
        
        MvGl2DemoMatrixTranslate(mModelMatrix, x, y, z);
        return;
    }


    void Entity::rotate (Real x, Real y, Real z)
    {
        MvGl2DemoMatrixRotate(mModelMatrix, x, 1.0f, 0.0f, 0.0f);
        MvGl2DemoMatrixRotate(mModelMatrix, y, 0.0f, 1.0f, 0.0f);
        MvGl2DemoMatrixRotate(mModelMatrix, z, 0.0f, 0.0f, 1.0f);

        return;
    }

    Material* Entity::getMaterial ()
    {
        return mMaterial;
    }



TOY3D_END_NAMESPACE
