uniform mat4 mvpMatrix;
attribute vec4 vVertex;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvpMatrix * vVertex;
}
