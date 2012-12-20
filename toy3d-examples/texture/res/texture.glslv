
//uniform mat4 proj_mat;   // Projection matrix.
//uniform mat4 mview_mat;  // Model-view matrix

attribute vec3 vPosition;
attribute vec2 vTexture;

varying vec2 v_texCoord;

void main()
{
	gl_Position = vec4(vPosition, 1.0);
	v_texCoord = vTexture;
}
