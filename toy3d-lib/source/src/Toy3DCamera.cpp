

#include "Toy3DCamera.h"
#include "Toy3DMath.h"
#include "Toy3DWorld.h"

TOY3D_BEGIN_NAMESPACE

    Camera::Camera(World *world) 
    {
        mWorld = world;
    }

    Camera::~Camera() 
    {
        
    }


    void Camera::lookAt (Real eyex, Real eyey, Real eyez,
        Real centerx, Real centery, Real centerz, Real upx, Real upy, Real upz)
    {

        MvGl2DemoMatrixIdentity(mViewMatrix);
        MvGl2DemoMatrixTranslate(mViewMatrix, eyex, eyey, eyez);
        //MvGl2DemoMatrixRotate(mViewMatrix, 20.0f, 1.0f, 0.0f, 0.0f);
        //MvGl2DemoMatrixRotate(mViewMatrix, 30.0f, 0.0f, 1.0f, 0.0f);
        //MvGl2DemoMatrixRotate(mViewMatrix,  0.0f, 0.0f, 0.0f, 1.0f);

    }

    void Camera::perspective (Real left, Real right, Real bottom, Real top, Real n, Real f)
    {

        MvGl2DemoMatrixIdentity(mProjectionMatrix);
        frustum (mProjectionMatrix, left, right, bottom, top, n, f);
        return;
    }

    void Camera::perspective (Real fovy, Real aspect, Real n, Real f)
    {
        Real xmin, xmax, ymin, ymax;
        ymax = n * tan (fovy * M_PI / 360);
        ymin = -ymax;
        xmin = ymin * aspect;
        xmax = ymax * aspect;

        perspective (xmin, xmax, ymin, ymax, n, f);
    }

    void Camera::ortho2D (Real left, Real right, Real bottom, Real top, Real n, Real f)
    {

        MvGl2DemoMatrixIdentity(mProjectionMatrix);
        ortho (mProjectionMatrix, left, right, bottom, top, n, f);
        return;
    }


    void Camera::getViewMatrix (Real m[MATRIX_4x4_SIZE])
    {
        int i = 0;
    
        for (i = 0; i < MATRIX_4x4_SIZE; i++)
            m[i] = mViewMatrix[i];

        return;
    }


    void Camera::getProjectionMatrix (Real m[MATRIX_4x4_SIZE])
    {

        int i = 0;
    
        for (i = 0; i < MATRIX_4x4_SIZE; i++)
            m[i] = mProjectionMatrix[i];


        return;
    }


    void Camera::frustum(Real m[MATRIX_4x4_SIZE],
                    Real l, Real r, Real b, Real t, Real n, Real f)
    {
        Real m1[MATRIX_4x4_SIZE];
        Real rightMinusLeftInv, topMinusBottomInv, farMinusNearInv, twoNear;

        rightMinusLeftInv = 1.0f / (r - l);
        topMinusBottomInv = 1.0f / (t - b);
        farMinusNearInv = 1.0f / (f - n);
        twoNear = 2.0f * n;

        m1[ 0] = twoNear * rightMinusLeftInv;
        m1[ 1] = 0.0f;
        m1[ 2] = 0.0f;
        m1[ 3] = 0.0f;

        m1[ 4] = 0.0f;
        m1[ 5] = twoNear * topMinusBottomInv;
        m1[ 6] = 0.0f;
        m1[ 7] = 0.0f;

        m1[ 8] = (r + l) * rightMinusLeftInv;
        m1[ 9] = (t + b) * topMinusBottomInv;
        m1[10] = -(f + n) * farMinusNearInv;
        m1[11] = -1.0f;

        m1[12] = 0.0f;
        m1[13] = 0.0f;
        m1[14] = -(twoNear * f) * farMinusNearInv;
        m1[15] = 0.0f;

        MvGl2DemoMatrixMultiply (m, m1);
    }


    void Camera::ortho(float m[MATRIX_4x4_SIZE],
                  float l, float r, float b, float t, float n, float f)
    {
        float m1[MATRIX_4x4_SIZE];
        float rightMinusLeftInv, topMinusBottomInv, farMinusNearInv;

        rightMinusLeftInv = 1.0f / (r - l);
        topMinusBottomInv = 1.0f / (t - b);
        farMinusNearInv = 1.0f / (f - n);

        m1[ 0] = 2.0f * rightMinusLeftInv;
        m1[ 1] = 0.0f;
        m1[ 2] = 0.0f;
        m1[ 3] = 0.0f;

        m1[ 4] = 0.0f;
        m1[ 5] = 2.0f * topMinusBottomInv;
        m1[ 6] = 0.0f;
        m1[ 7] = 0.0f;

        m1[ 8] = 0.0f;
        m1[ 9] = 0.0f;
        m1[10] = -2.0f * farMinusNearInv;
        m1[11] = 0.0f;

        m1[12] = -(r + l) * rightMinusLeftInv;
        m1[13] = -(t + b) * topMinusBottomInv;
        m1[14] = -(f + n) * farMinusNearInv;
        m1[15] = 1.0f;

        MvGl2DemoMatrixMultiply(m, m1);
    }

    void Camera::renderScene(Viewport *vp)
    {

        mWorld->renderScene (this, vp);

    }




TOY3D_END_NAMESPACE
