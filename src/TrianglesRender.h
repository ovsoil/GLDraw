/*
 * TrianglesRender.h
 *
 *  Created on: 2015-01-03
 *      Author: ovsoil
 */

#ifndef TRIANGLESRENDER_H_
#define TRIANGLESRENDER_H_

#include <GLTools.h>
#include <GLShaderManager.h>
#include "TexturesManager.h"

#include "GLTexture.h"

struct TexPair
{
    const char* texname;
    const char* texfile;
};

enum TEXTURE
{
    TEXTURE_1 = 0,
    TEXTURE_2,
    TEXTURE_COUNT
};

static const TexPair textures[TEXTURE_COUNT] = {
    {"tex1", "resources/brick.tga"},
    {"tex2", "resources/floor.tga"}
};

class TrianglesRender
{
public:
    TrianglesRender();
    ~TrianglesRender();

    void SetupRC();
    void CleanRC();
    void Render();

private:
    inline void initPrograms()
    {
        shaderManager.InitializeStockShaders();
    }
    inline void initTextures()
    {
        for(int i = 0; i < TEXTURE_COUNT; ++i)
        {
            TexturesManager::GetSingletonPtr()->AddTexture(textures[i].texfile, textures[i].texname);
        }
    }

private:
    GLBatch  triangle1, triangle2, triangle3;
    
    GLuint texturesID[TEXTURE_COUNT];                     //纹理
    //Gluint shaders;

    GLShaderManager shaderManager;      //用GLShaderManager中定义好的shader

public:
    //直接设置MVP矩阵（或者分开设置Model, View, Project)。
    //TODO: 利用视图类获取变换矩阵，视图类控制交互与坐标变换。
    void SetMVP(const M3DMatrix44f mvp);
private:
    M3DMatrix44f mvpMatrix;
};

#endif /* TRIANGLESRENDER_H_ */
