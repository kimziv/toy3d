
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

    

//≤‚ ‘”√
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

#define TOY3D_PRINT(str, file, line) printf("%s, File:%s, Line:%d.\n", str, file, line)


//#define PRINT(file, format, ...) myprintf(file, format, ##args)
//#define PRINT(file, format, args...) myprintf(file, format, __VA_ARGS__)



/*********************************
*  define type  
**********************************/

    typedef float  Real;
    typedef double DReal;

    #define FALSE       0
    #define TRUE        1
    typedef int Bool;




    typedef unsigned char  Uchar;
    typedef unsigned short Ushort;
    typedef unsigned int   Uint;
    typedef unsigned long  Ulong;

    typedef signed char  Schar;
    typedef signed short Sshort;
    typedef signed int   Sint;
    typedef signed long  Slong;




     enum RenderMode {
        TOY3D_POINTS = 1,
        TOY3D_LINES = 2,
        TOY3D_LINE_STRIP = 3,
        TOY3D_TRIANGLES = 4,
        TOY3D_TRIANGLE_STRIP = 5,
        TOY3D_TRIANGLE_FAN = 6
     };

     enum AutoConstantType
     {
         TOY3D_ACT_WORLD_MATRIX,
         TOY3D_ACT_VIEW_MATRIX, 
         TOY3D_ACT_PROJECTION_MATRIX
     };

     enum AttrConstantType
     {
         TOY3D_ATTR_VERTEX_INDEX,
         TOY3D_ATTR_COLOR_INDEX, 
         TOY3D_ATTR_UV_INDEX,
         TOY3D_ATTR_NORMAL_INDEX
     };





#ifdef __cplusplus
}
#endif

#endif //_TOY3D_COMMON_H

