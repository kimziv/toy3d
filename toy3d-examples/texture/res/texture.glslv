
uniform mat4 proj_mat;   // Projection matrix.
uniform mat4 view_mat;  // View matrix
uniform mat4 world_mat;  // Model matrix

attribute vec3 vPosition;
attribute vec2 vTexture;

varying vec2 v_texCoord;

void main()
{
	//gl_Position = vec4(vPosition, 1.0);
	gl_Position = proj_mat * view_mat * world_mat * vec4(vPosition, 1.0);
	v_texCoord = vTexture;
}
