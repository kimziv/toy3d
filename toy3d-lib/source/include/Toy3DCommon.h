
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

//////////////////////////////////////////////////////////////////////////
//config
    
//binary file format.
#define BINARY_CODE_FOR_NV  0x890B

#define DEFAULT_PTR_ARRAY_SIZE 8
#define MAX_ENTITY_COUNT       8
/* Warning:
 * Parameter list length must be less than the values.
 * And now, no fault tolerance in the code.
 */
//#define MAX_AUTOENTRY_COUNT 8
//#define MAX_ATTRENTRY_COUNT 8
//#define MAX_CUSTENTRY_COUNT 8

//#define MAX_MESH_COUNT      8
//#define MAX_TEXTURE_COUNT   8
//#define MAX_MATERIAL_COUNT  8
//#define MAX_SHADER_PROGRAM_COUNT 8
//#define MAX_SHADER_PROGRAM_PARAMS_COUNT 8


//max length of name
#define MAX_NAME_LEN        31
#define MAX_NAME_LEN_BIG    127

#define MATRIX_4x4_SIZE     16

//size of custom uniform base unit
//#define CUSTOM_UNIT_SIZE 4

//error code
#define TOY3D_ERROR -1



//////////////////////////////////////////////////////////////////////////
//

#ifndef M_PI
#define M_PI 3.1415926535897932f
#endif



#define FREEANDNULL(pointer) \
    if (pointer != NULL) { \
        free(pointer); \
        pointer = NULL; \
    }

#define DELETEANDNULL(pointer) \
    if (pointer != NULL) { \
        delete pointer; \
        pointer = NULL; \
    }


#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

//used for testing
#define TOY3D_PRINT(str, file, line) printf("%s, File:%s, Line:%d.\n", str, file, line)
//used to indicate the user
#define TOY3D_TIPS(strError) printf("Error: %s\n", strError)


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

    
    enum RenderMode
    {
        TOY3D_POINTS = 1,
        TOY3D_LINES = 2,
        TOY3D_LINE_STRIP = 3,
        TOY3D_TRIANGLES = 4,
        TOY3D_TRIANGLE_STRIP = 5,
        TOY3D_TRIANGLE_FAN = 6
    };
    
    enum AutoConstanType
    {
        TOY3D_ACT_WORLD_MATRIX,
        TOY3D_ACT_VIEW_MATRIX, 
        TOY3D_ACT_PROJECTION_MATRIX,
        TOY3D_ACT_SAMPLER2D
    };

    enum AttrConstantType
    {
        TOY3D_ATTR_VERTEX,
        TOY3D_ATTR_COLOR, 
        TOY3D_ATTR_UV,
        TOY3D_ATTR_NORMAL
    };

    
    enum CustUniformConstanType
    {
        TOY3D_CUST_INT1,
        TOY3D_CUST_INT2,
        TOY3D_CUST_INT3,
        TOY3D_CUST_INT4,
        TOY3D_CUST_REAL1,
        TOY3D_CUST_REAL2,
        TOY3D_CUST_REAL3,
        TOY3D_CUST_REAL4,
        TOY3D_CUST_SAMPLER1D,
        TOY3D_CUST_SAMPLER2D,
        TOY3D_CUST_SAMPLER3D,
        TOY3D_CUST_SAMPLERCUBE,
        TOY3D_CUST_MATRIX_2,
        TOY3D_CUST_MATRIX_3,
        TOY3D_CUST_MATRIX_4,
        TOY3D_CUST_VEC_2,
        TOY3D_CUST_VEC_3,
        TOY3D_CUST_VEC_4,
		TOY3D_CUST_UNKNOWN = 99
    };
    
    
    typedef struct _ImageInfo
    {
        unsigned char *pImageData; /* color data of image */
        Uint width;                /* width of image */
        Uint height;               /* height of image */
        Uint bpp;                  /* bytes per pixel */
    }ImageInfo;

    enum BlendingFactor
    {
        /* Blending Factor Dest */
        T3D_ZERO,
        T3D_ONE,
        T3D_SRC_COLOR,
        T3D_ONE_MINUS_SRC_COLOR,
        T3D_SRC_ALPHA,
        T3D_ONE_MINUS_SRC_ALPHA,
        T3D_DST_ALPHA,
        T3D_ONE_MINUS_DST_ALPHA,

        /* Blending Factor Src */
        /* T3D_ZERO */
        /* T3D_ONE */
        T3D_DST_COLOR,
        T3D_ONE_MINUS_DST_COLOR,
        T3D_SRC_ALPHA_SATURATE,
        /* T3D_SRC_ALPHA */
        /* T3D_ONE_MINUS_SRC_ALPHA */
        /* T3D_DST_ALPHA */
        /* T3D_ONE_MINUS_DST_ALPHA */
    };
    
    enum BlendingMode
    {
        T3D_ADD,
        T3D_SUBTRACT,
        T3D_REVERSE_SUBTRACT,
        T3D_MIN,
        T3D_MAX
    };

    /*
    typedef struct _BlendingInfo
    {
        BlendingFactor srcFactor;
        BlendingFactor destFactor;
        BlendingMode   mode;
    }BlendingInfo;
    */



#ifdef __cplusplus
}
#endif

#endif //_TOY3D_COMMON_H

