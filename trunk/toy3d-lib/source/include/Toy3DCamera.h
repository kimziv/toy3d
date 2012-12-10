
#ifndef _TOY3D_CAMERA_H
#define _TOY3D_CAMERA_H

#include "Toy3DCommon.h"

TOY3D_BEGIN_NAMESPACE

#define MATRIX_MAX  16

    class Camera 
    {

	private:
        Real mProjectionMatrix[MATRIX_MAX];
        Real mViewMatrix[MATRIX_MAX];

/*
        Matrix4 mProjectionMatrix;
        Matrix4 mViewMatrix;
*/

	public:

        Camera();
        ~Camera();

    public:
        void lookAt (Real eyex, Real eyey, Real eyez, Real centerx, Real centery, Real centerz, Real upx, Real upy, Real upz);
        //void perspcective (Real angle, Real aspect, Real near, Real far);
        void perspcective (Real left, Real right, Real bottom, Real top, Real near, Real far);
        void getViewMatrix (Real m[MATRIX_MAX]);
        void getProjectionMatrix (Real m[MATRIX_MAX]);

    public:
        void frustum(Real m[16],
                    Real l, Real r, Real b, Real t, Real n, Real f);


    };



TOY3D_END_NAMESPACE

#endif
