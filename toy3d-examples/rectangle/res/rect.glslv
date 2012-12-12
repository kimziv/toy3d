
uniform mat4 proj_mat;   // Projection matrix.
uniform mat4 mview_mat;  // Model-view matrix
attribute vec3 pos_attr;


void main()
{
	gl_Position = proj_mat * mview_mat * vec4(pos_attr, 1.0);
}
