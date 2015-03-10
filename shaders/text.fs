uniform sampler2D texUnit;

void main()
{
    float a = texture2D(texUnit, gl_TexCoord[0].xy).r;
    gl_FragColor = vec4(gl_Color.rgb, gl_Color.a*a);
}
