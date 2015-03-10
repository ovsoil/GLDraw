uniform sampler2D textureUnit;
varying vec2 varyingTexCoords;

void main()
{
    // Set fragment color from texture
    gl_FragColor = texture2D(textureUnit, varyingTexCoords);
}

