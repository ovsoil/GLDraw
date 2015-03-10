uniform mat4 MVP;

attribute vec3 vertex;
attribute vec2 tex_coord;
attribute vec4 color;
void main()
{
    gl_TexCoord[0].xy = tex_coord.xy;
    gl_FrontColor     = color;
    gl_Position       = MVP * vec4(vertex,1.0);
}
