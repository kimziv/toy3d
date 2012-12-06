
#ifndef _TOY3D_COMMON_H_
#define _TOY3D_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef OPENGL

#ifdef MAC
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif  //end of MAC

#else 
#include <GLES/gl.h>
//#include <android/log.h>
#endif  //end of OPENGL

#define TOY3D_BEGIN_NAMESPACE namespace TOY3D {
#define TOY3D_END_NAMESPACE }

typedef float Real;






#ifndef M_PI
#define M_PI 3.1415926535897932f
#endif



#define FREEANDNULL(pointer) \
    if (pointer != NULL) { \
        free(pointer); \
        pointer = NULL; \
    }



#ifdef __cplusplus
}
#endif

#endif //_TOY3D_COMMON_H

