const float c_one  = 1.0;
const float c_zero = 0.0;

precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_baseMap;
uniform sampler2D s_lightMap;

void main()
{
    vec4 baseColor;
    vec4 lightColor;
    vec4 finalColor;

    baseColor = texture2D( s_baseMap, v_texCoord );
    lightColor = texture2D( s_lightMap, v_texCoord );
    gl_FragColor = baseColor * (lightColor + 0.25);
    //gl_FragColor = vec4(1.0, 0.0, 0.0, 0.0);
    
    //finalColor = mix(baseColor, lightColor, lightColor.a);
    //gl_FragColor = clamp( finalColor, c_zero, c_one );
}

