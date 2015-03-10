/*
 * TextRender.h
 *
 *  Created on: 2015-01-13
 *      Author: ovsoil
 */

#ifndef TEXTRENDER_H_
#define TEXTRENDER_H_

#include <wchar.h>
#include "freetype-gl.h"
#include "vertex-buffer.h"
#include "shader.h"
#include "mat4.h"

#include <GLTools.h>

#include <iostream>
using std::cout;
using std::endl;

typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
    float r, g, b, a; // color
} vertex_t;

static const wchar_t *text = L"A Quick Brown Fox Jumps Over The Lazy Dog 0123456789 ";

class TextRender
{
public:
    TextRender();
    ~TextRender();

    void AddText(const wchar_t *text, vec4 *color, vec2 *pen);
    void SetupRC();
    void Update();
    void CleanRC();
    void Render();

private:
    inline void initPrograms()
    {
        shader = shader_load("shaders/text.vs",
                         "shaders/text.fs");
    }
    inline void initTextures()
    {
        atlas  = texture_atlas_new( 512, 512, 1 );
        font = texture_font_new_from_file( atlas, 12, "resources/fonts/VeraMono.ttf" );
    }

private:
    texture_atlas_t *atlas;
    texture_font_t *font;
    vertex_buffer_t *buffer;

    //mat4 model, view, projection;
    GLuint shader;

public:
    //直接设置MVP矩阵（或者分开设置Model, View, Project)。
    //TODO: 利用视图类获取变换矩阵，视图类控制交互与坐标变换。
    void SetMVP(const M3DMatrix44f mvp);
private:
    M3DMatrix44f mvpMatrix;
};

#endif /* TEXTRENDER_H_ */
