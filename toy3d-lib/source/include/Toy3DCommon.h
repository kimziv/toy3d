
#ifndef _TOY3D_COMMON_H_
#define _TOY3D_COMMON_H_




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include <GL/glew.h>
#include <GL/glut.h>




#ifdef __cplusplus
extern "C" {
#endif



#define TOY3D_BEGIN_NAMESPACE namespace TOY3D {
#define TOY3D_END_NAMESPACE }


    //数据类型定义
    typedef float  Real;
    typedef double DReal;
    typedef boolean   Bool;

    typedef unsigned char  Uchar;
    typedef unsigned short Ushort;
    typedef unsigned int   Uint;
    typedef unsigned long  Ulong;

    typedef signed char  Schar;
    typedef signed short Sshort;
    typedef signed int   Sint;
    typedef signed long  Slong;


//测试用
#define MAX_MESH_COUNT      8
#define MAX_AUTOENTRY_COUNT 8
#define MAX_NAME_LEN        32
#define MATRIX_4x4_SIZE     16


#ifndef M_PI
#define M_PI 3.1415926535897932f
#endif



#define FREEANDNULL(pointer) \
    if (pointer != NULL) { \
        free(pointer); \
        pointer = NULL; \
    }

    void PRINT( char * format, ...);


//#define PRINT(file, format, ...) myprintf(file, format, ##args)
//#define PRINT(file, format, args...) myprintf(file, format, __VA_ARGS__)


#define MATRIX_SIZE 16





#ifdef __cplusplus
}
#endif

#endif //_TOY3D_COMMON_H

