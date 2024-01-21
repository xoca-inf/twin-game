varying vec2 vTexCoord;
uniform sampler2D texture0;

void w4_main()
{
    vec4 resultColor = texture2D(texture0, vTexCoord);
    if (resultColor.a < 0.001) discard;
    
    gl_FragColor = resultColor;
}
