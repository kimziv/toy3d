
precision medium float;

uniform sampler2D sampler2d;
varying vec2 v_texCoord;

void main()
{
    gl_FragColor = texture2D(sampler2d, v_texCoord);
}
