
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

typedef float Real;

typedef unsigned char Uchar;
typedef unsigned short Ushort;
typedef unsigned int Uint;
typedef unsigned long Ulong;

typedef signed int Sint;






#ifndef M_PI
#define M_PI 3.1415926535897932f
#endif



#define FREEANDNULL(pointer) \
    if (pointer != NULL) { \
        free(pointer); \
        pointer = NULL; \
    }




#define MATRIX_SIZE 16





#ifdef __cplusplus
}
#endif

#endif //_TOY3D_COMMON_H

