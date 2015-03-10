uniform mat4 MVP;
attribute vec4 attr_vertex;
attribute vec4 attr_color;
attribute vec2 attr_texc;
varying vec4 vary_color;
varying vec2 vary_texc;


void main()
{
    // Calculate vertex position in screen space
    gl_Position = MVP * attr_vertex;
    vary_color = attr_color;
    vary_texc = attr_texc;
}
