/*
 * TexturesManager.cpp
 *
 *  Created on: 2015-01-10
 *      Author: ovsoil
 */
#include "TexturesManager.h"

TexturesManager::TexturesManager()
{
}
TexturesManager::~TexturesManager()
{
}
void TexturesManager::InitTexturesLocation()
{
    //TODO： 初始化目录，以便在AddTexture中不用指定完整文件名
}

GLuint TexturesManager::AddTexture(const string& fileName, const string& texName,
            GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{

    GLTexture *pTex = new GLTexture2D(fileName, minFilter, magFilter, wrapMode);
    texMaps[texName] = pTex;
    return pTex->GetID();
}


GLTexture* TexturesManager::GetTexture(const string& texName)
{
    return texMaps[texName];
}

void SetTexture(const string& texName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
    //TODO
}

void TexturesManager::DelTexture(const string& texName)
{
    //TODO
}
