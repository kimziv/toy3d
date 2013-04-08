#ifndef _USER_DATA_H
#define _USER_DATA_H


#ifdef __cplusplus
extern "C" {
#endif



#define WINDOW_W    800
#define WINDOW_H    600
    
    
#ifdef VC6
#define SHADER_VERT_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/framelistener/framelistener.glslv"
#define SHADER_FRAG_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/framelistener/framelistener.glslf"
#else
#define SHADER_VERT_FILE "/usr/local/share/toy3d/rectangle/framelistener.glslv"
#define SHADER_FRAG_FILE "/usr/local/share/toy3d/rectangle/framelistener.glslf"
#endif
    




#ifdef __cplusplus
}
#endif



#endif