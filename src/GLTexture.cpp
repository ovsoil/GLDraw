#include "GLTexture.h"
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

//============================================================================//
//                                  GLTexture                                 //
//============================================================================//
GLTexture::GLTexture() : m_texture(-1), m_failed(false)
{
    cout << "GLTexture()" << endl;
    glEnable(GL_TEXTURE_2D);
    cout << m_texture << endl;
    glGenTextures(1, &m_texture);
    cout << m_texture << endl;
}

GLTexture::~GLTexture()
{
    cout << "~GLTexture()" << endl;
    glDeleteTextures(1, &m_texture);
}

//============================================================================//
//                                 GLTexture2D                                //
//============================================================================//
//GLTexture2D::GLTexture2D()
//{
//}

GLTexture2D::GLTexture2D(int width, int height, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);

    if(minFilter == GL_LINEAR_MIPMAP_LINEAR || 
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    m_failed = true;
}

GLTexture2D::GLTexture2D(const string& fileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
    if( !LoadFromTga(fileName, minFilter, magFilter, wrapMode) )
        m_failed = false;
    else
        m_failed = true;
}

bool GLTexture2D::LoadFromTga(const string& tgaName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
    // TODO: Add error handling.
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    
    pBytes = gltReadTGABits(tgaName.c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
    if(pBytes == NULL)
    {
        printf("Textrue file load failed!\n");
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, m_texture);
    // Load texture, set filter and wrap modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);


    if(minFilter == GL_LINEAR_MIPMAP_LINEAR || 
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);
    // Don't need original texture data any more
    free(pBytes);
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

void GLTexture2D::Load(int width, int height, GLbyte *data)
{
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_BGRA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture2D::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    //glEnable(GL_TEXTURE_2D);
}

void GLTexture2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_TEXTURE_2D);
}
