#ifndef _USER_DATA_H
#define _USER_DATA_H


#ifdef __cplusplus
extern "C" {
#endif



#define WINDOW_W    800
#define WINDOW_H    600
    
    
#ifdef VC6
#define SHADER_VERT_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/fbo/fbo.glslv"
#define SHADER_FRAG_FILE_WIN "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/fbo/fbo_win.glslf"
#define SHADER_FRAG_FILE_TEX "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/fbo/fbo_tex.glslf"
#define TEXTURE_FILE     "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/fbo/leaf.tga"
#else 
#define SHADER_VERT_FILE "/usr/local/share/toy3d/fbo/fbo.glslv"
#define SHADER_FRAG_FILE_WIN "/usr/local/share/toy3d/fbo/fbo_win.glslf"
#define SHADER_FRAG_FILE_TEX "/usr/local/share/toy3d/fbo/fbo_tex.glslf"
#define TEXTURE_FILE     "/usr/local/share/toy3d/fbo/leaf.tga"
#endif



#ifdef __cplusplus
}
#endif



#endif