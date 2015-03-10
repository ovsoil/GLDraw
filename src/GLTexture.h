#ifndef GLTEXTURE_H
#define GLTEXTURE_H
#include <GLTools.h>

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

class GLTexture
{
public:
    GLTexture();
    virtual ~GLTexture();
    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual bool Failed() const {return m_failed;}
protected:
    GLuint m_texture;
    bool m_failed;

public:
    inline void Print(){cout << m_texture << endl;}
    inline GLuint GetID(){ return m_texture; }
};


class GLTexture2D : public GLTexture
{
private:
    //GLTexture2D(const GLTexture2D& );
public:
    //GLTexture2D();
    ~GLTexture2D(){cout << "~GLTexture2D()" << endl;}

    GLTexture2D(int width, int height,
            GLenum minFilter = GL_REPEAT, GLenum magFilter = GL_LINEAR, GLenum wrapMode = GL_LINEAR);
    explicit GLTexture2D(const string& fileName,
            GLenum minFilter = GL_REPEAT, GLenum magFilter = GL_LINEAR, GLenum wrapMode = GL_LINEAR);


    bool LoadFromTga(const string& tgaName,
            GLenum minFilter = GL_REPEAT, GLenum magFilter = GL_LINEAR, GLenum wrapMode = GL_LINEAR);
    void Load(int width, int height, GLbyte *data);

    virtual void Bind();
    virtual void Unbind();
};

#endif // GLTEXTURE_H
