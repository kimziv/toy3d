
precision medium float;

uniform sampler2D sampler2d;
uniform float limit;
varying vec2 v_texCoord;

void main()
{
    vec4 color = texture2D(sampler2d, v_texCoord);
	float alph = color.a;
    if(alph<limit)
    {
        discard;
    }
    else
    {
        gl_FragColor = color;
    }
}
