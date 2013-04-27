#ifndef _USER_DATA_H
#define _USER_DATA_H


#ifdef __cplusplus
extern "C" {
#endif



#define WINDOW_W    600
#define WINDOW_H    600
    
    
#ifdef VC6
#define SHADER_VERT_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/fbo_mini_screen/fbo_mini.glslv"
#define SHADER_FRAG_FILE_RENDER "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/fbo_mini_screen/render.glslf"
#define SHADER_FRAG_FILE_RENDER_WITH_TEX "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/fbo_mini_screen/render_with_texture.glslf"

#else 
#define SHADER_VERT_FILE "/usr/local/share/toy3d/fbo_mini_screen/fbo_mini.glslv"
#define SHADER_FRAG_FILE_RENDER "/usr/local/share/toy3d/fbo_mini_screen/render.glslf"
#define SHADER_FRAG_FILE_RENDER_WITH_TEX "/usr/local/share/toy3d/fbo_mini_screen/render_with_texture.glslf"
#endif



#ifdef __cplusplus
}
#endif



#endif