
#ifndef _TOY3D_MATH_H_
#define _TOY3D_MATH_H_



#ifdef __cplusplus
extern "C" {
#endif


// Math stuff

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#define eps 1e-4

int eq(float a, float b);

void MvGl2DemoMatrixIdentity(float m[16]);

int MvGl2DemoMatrixEquals(float a[16], float b[16]);  

void MvGl2DemoMatrixTranspose(float m[16]);

void MvGl2DemoMatrixMultiply(float m0[16], float m1[16]);

void MvGl2DemoMatrixMultiply_4x4_3x3(float m0[16], float m1[9]);

void MvGl2DemoMatrixMultiply_3x3(float m0[9], float m1[9]);

void MvGl2DemoMatrixFrustum(float m[16],
                    float l, float r, float b, float t, float n, float f);

void MvGl2DemoMatrixOrtho(float m[16],
                  float l, float r, float b, float t, float n, float f);

void MvGl2DemoMatrixTranslate(float m[16], float x, float y, float z);

void MvGl2DemoMatrixRotate_create3x3(float m[9],
                             float theta, float x, float y, float z);

void MvGl2DemoMatrixRotate(float m[16], float theta, float x, float y, float z);


void MvGl2DemoMatrixRotate_3x3(float m[9], float theta, float x, float y, float z);

float MvGl2DemoMatrixDeterminant(float m[16]); 

void MvGl2DemoMatrixInverse(float m[16]); 


void MvGl2DemoMatrixCopy(float dest[16], float src[16]);  

void MvGl2DemoMatrixPrint(float a[16]);  

void MvGl2DemoMatrixVectorMultiply(float m[16],  float v[4]); 


#ifdef __cplusplus
}
#endif


#endif //_TOY3D_MATH_H
