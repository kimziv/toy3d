

#include "Toy3DCamera.h"
#include "Toy3DMath.h"

TOY3D_BEGIN_NAMESPACE

    Camera::Camera() 
    {
    }

    Camera::~Camera() 
    {
    }


    void Camera::lookAt (Real eyex, Real eyey, Real eyez, Real centerx, Real centery, Real centerz, Real upx, Real upy, Real upz)
    {

        MvGl2DemoMatrixIdentity(mViewMatrix);
        MvGl2DemoMatrixTranslate(mViewMatrix, 0.0f, 0.0f, -40.0f);
        MvGl2DemoMatrixRotate(mViewMatrix, 20.0f, 1.0f, 0.0f, 0.0f);
        MvGl2DemoMatrixRotate(mViewMatrix, 30.0f, 0.0f, 1.0f, 0.0f);
        MvGl2DemoMatrixRotate(mViewMatrix,  0.0f, 0.0f, 0.0f, 1.0f);

    }

    void Camera::perspcective (Real left, Real right, Real bottom, Real top, Real n, Real f)
    {

        MvGl2DemoMatrixIdentity(mProjectionMatrix);
        frustum (mProjectionMatrix, left, right, bottom, top, n, f);
        return;
    }

    void Camera::getViewMatrix (Real m[MATRIX_MAX])
    {
        int i = 0;
    
        for (i = 0; i < MATRIX_MAX; i++)
            m[i] = mViewMatrix[i];

        return;
    }


    void Camera::getProjectionMatrix (Real m[MATRIX_MAX])
    {

        int i = 0;
    
        for (i = 0; i < MATRIX_MAX; i++)
            m[i] = mProjectionMatrix[i];


        return;
    }


    void Camera::frustum(Real m[16],
                    Real l, Real r, Real b, Real t, Real n, Real f)
    {
        Real m1[16];
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


/*
    void Camera::matrixMultiple(float m0[16], float m1[16])
    {

        int r, c, i;
        for(r = 0; r < 4; r++)
        {
            float m[4] = {0.0, 0.0, 0.0, 0.0};
            for(c = 0; c < 4; c++)
            {
                for(i = 0; i < 4; i++)
                {
                    m[c] += m0[4 * i + r] * m1[4 * c + i];
                }
            }
            for(c = 0; c < 4; c++) { m0[4 * c + r] = m[c]; }
        }


    }


    void Camera::matrixTranslate(float m[16], float x, float y, float z)
    {
        float m1[16];
        matrixIdentity(m1);

        m1[4 * 3 + 0] = x;
        m1[4 * 3 + 1] = y;
        m1[4 * 3 + 2] = z;

        matrixMultiply(m, m1);
    }
*/



TOY3D_END_NAMESPACE
