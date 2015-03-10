/*
 * TexturesManager.h
 *
 *  Created on: 2015-01-10
 *      Author: ovsoil
 */

#ifndef TEXTURESMANAGER_H_
#define TEXTURESMANAGER_H_
#include <map>
#include <string>
using std::map;
using std::string;

#include <GLTools.h>
#include "Singleton.h"
#include "GLTexture.h"

class TexturesManager : public ISingleton<TexturesManager>
{
public:
    TexturesManager();
    ~TexturesManager();

    void InitTexturesLocation();
    GLuint AddTexture(const string& fileName, const string& texName,
            GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR, GLenum wrapMode = GL_LINEAR);

    GLTexture* GetTexture(const string& texName);
    void SetTexture(const string& texName, 
            GLenum minFilter, GLenum magFilter, GLenum wrapMode);

    void DelTexture(const string& texName);
private:
    map<string, GLTexture*> texMaps;

    friend class ISingleton<TexturesManager>;
    friend class auto_ptr<TexturesManager>;
};

#endif //TEXTURESMANAGER_H_
