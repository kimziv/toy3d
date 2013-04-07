
precision medium float;

const int c_one = 1;

uniform sampler2D sampler2d;
uniform float limit;
//uniform int flag;
varying vec2 v_texCoord;

void main()
{
    static int temp = 0;
	if(temp != c_one)
	{
	    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
		temp = 1;
		return;
	}
	
	gl_FragColor = texture2D(sampler2d, v_texCoord);
	temp = 0;
	return;
}
