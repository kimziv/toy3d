
#ifndef _TOY3D_CAMERA_H
#define _TOY3D_CAMERA_H

#include "Toy3DCommon.h"
//#include "Toy3DWorld.h"

TOY3D_BEGIN_NAMESPACE

    class World;
    class Viewport;

    class Camera 
    {
	private:
        Real mProjectionMatrix[MATRIX_4x4_SIZE];
        Real mViewMatrix[MATRIX_4x4_SIZE];
        World *mWorld;

	public:
        Camera(World *world);
        ~Camera();

    public:
        void lookAt (Real eyex, Real eyey, Real eyez, Real centerx, Real centery, Real centerz, Real upx, Real upy, Real upz);
        void perspective (Real left, Real right, Real bottom, Real top, Real n, Real f);
        void perspective (Real fovy, Real aspect, Real n, Real f);
        void ortho2D (Real left, Real right, Real bottom, Real top, Real n, Real f);
        void getViewMatrix (Real m[MATRIX_4x4_SIZE]);
        void getProjectionMatrix (Real m[MATRIX_4x4_SIZE]);



    public:
        void frustum(Real m[MATRIX_4x4_SIZE], Real l, Real r, Real b, Real t, Real n, Real f);
        void ortho(Real m[MATRIX_4x4_SIZE], Real l, Real r, Real b, Real t, Real n, Real f);


    public:
        void renderScene(Viewport *vp);

    };



TOY3D_END_NAMESPACE

#endif
