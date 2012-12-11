#include "Toy3DCommon.h"

void PRINT( char * format, ...) 
{
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vprintf(format, arg_ptr);
    va_end(arg_ptr);
}
