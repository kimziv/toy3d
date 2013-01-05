
precision medium float;

uniform sampler2D sampler2d;
uniform float limit;
varying vec2 v_texCoord;

void main()
{
    if(limit>1.0)
    {
        discard;
    }
    else
    {
        gl_FragColor = texture2D(sampler2d, v_texCoord);
    }
}
