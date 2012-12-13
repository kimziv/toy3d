
//uniform mat4 proj_mat;   // Projection matrix.
//uniform mat4 mview_mat;  // Model-view matrix
//attribute vec3 pos_attr;
attribute vec4 vPosition;


void main()
{
	gl_Position = vPosition;
}
