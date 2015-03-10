#ifdef OPENGL_ES
    precision mediump float;
#endif
uniform sampler2D texUnit;
varying vec4 vary_color;
varying vec2 vary_texc;

void main()
{
    gl_FragColor = texture2D(texUnit, vary_texc);
    //gl_FragColor = vary_color * texture2D(texUnit, vary_texc);
}
