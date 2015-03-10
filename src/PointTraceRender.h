/*
 * PointTraceRender.h
 *
 *  Created on: 2015-01-08
 *      Author: ovsoil
 */

#ifndef POINTTRACERENDER_H
#define POINTTRACERENDER_H

//#include "symboltexture.h"
#include <GLTools.h>
#include <GLShaderManager.h>
#include "TexturesManager.h"

//#include <vector>
//#include <string>
//
//using std::string;
//using std::vector;

enum PROGRAM_FLAG
{
    PROGRAM_BROW = 0,
    PROGRAM_SYMBOL,
    PROGRAM_COUNT
};

static const char* ShaderName[PROGRAM_COUNT] = {"brow", "symbol"};
static const char* TextureName[1] = {"symbol"};

class PointTraceRender// : protected QGLFunctions
{
public:
    PointTraceRender();
    ~PointTraceRender();

    void SetupRC();
    void Update();
    void CleanRC();
    void Render();

    void SetMVP(const M3DMatrix44f mvp);
private:

    //program 和 Textures的管理可以重新考虑
    inline void initPrograms()
    {
        shaderManager.InitializeStockShaders();
        for(int i = 0; i < PROGRAM_COUNT; ++i)
        {
            string strVp = string("shaders/") + string(ShaderName[i]) + string(".vs");
            string strFp = string("shaders/") + string(ShaderName[i]) + string(".fs");
	        programs[i] = gltLoadShaderPairWithAttributes(strVp.c_str(), strFp.c_str(), 2, 
		                            GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_TEXTURE0, "vTexCoords");
        }
    }

    inline void initTextures()
    {
        //texture.LoadFromTga("/home/ovsoil/4.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
        for(int i = 0; i < 1; ++i)
        {
            string fileName = string("resources/images/") + string(TextureName[i]) + string(".tga");
            TexturesManager::GetSingletonPtr()->AddTexture(fileName, TextureName[i]);
        }
    }

private:
    int num;
    M3DVector3f* vVerts_brow;
    M3DVector3f* vVerts_symbol;
    M3DVector2f* vTexCoords;

    GLBatch browBatch;
    GLBatch symbolBatch;

    GLShaderManager shaderManager;
    GLuint programs[PROGRAM_COUNT];
    //GLTexture2D texture;

    M3DMatrix44f mvpMatrix;


};
#endif // POINTTRACERENDER_H
