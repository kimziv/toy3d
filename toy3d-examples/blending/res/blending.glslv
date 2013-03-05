
//uniform mat4 proj_mat;   // Projection matrix.
//uniform mat4 mview_mat;  // Model-view matrix
//attribute vec3 pos_attr;
attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 fColor;
//varying vec2 v_st;

void main()
{
	gl_Position = vPosition;
    //v_st = vPosition.st;
	fColor = vColor;
	//gl_Color = vColor;
	//gl_FrontColor = vColor;
}
