uniform mat4 mvpMatrix;
attribute vec4 vVertex;
attribute vec2 vTexCoords;

varying vec2 varyingTexCoords;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvpMatrix * vVertex;
    varyingTexCoords = vTexCoords;
}
