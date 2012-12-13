
uniform mat4 proj_mat;   // Projection matrix.
uniform mat4 mview_mat;  // Model-view matrix
attribute vec3 vPosition;


void main()
{
	gl_Position = proj_mat * mview_mat * vec4(vPosition, 1.0);
}
