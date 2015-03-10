#ifndef TUNNELRENDER_H
#define TUNNELRENDER_H

#include <GLTools.h>
//#include <GLGeometryTransform.h>
#include <GLBatch.h>
#include <GLShaderManager.h>
#include "GLTexture.h"

#include <vector>
#include <string>
using std::vector;
using std::string;


#define TEXTURE_BRICK   0
#define TEXTURE_FLOOR   1
#define TEXTURE_CEILING 2
#define TEXTURE_COUNT   3
static const char *szTextureFiles[TEXTURE_COUNT] = { "/home/ovsoil/brick.tga", "/home/ovsoil/floor.tga", "/home/ovsoil/ceiling.tga" };

class TunnelRender
{
public:
    TunnelRender();
    ~TunnelRender();

    void SetupRC();
    void CleanRC();
    void Render();

    void SetMVP(const M3DMatrix44f mvp);
private:
    inline void initPrograms()
    {
        shaderManager.InitializeStockShaders();
    }
    inline void initTextures()
    {
        for(int i = 0; i < TEXTURE_COUNT; ++i)
        {
            textures.push_back(GLTexture2D(string(szTextureFiles[i])));
            textures[i].Print();
        }
    }

private:
    int num;
    vector<GLTexture2D> textures;

    GLBatch             floorBatch;
    GLBatch             ceilingBatch;
    GLBatch             leftWallBatch;
    GLBatch             rightWallBatch;

public:
    GLShaderManager		shaderManager;			// Shader Manager
    //GLGeometryTransform	transformPipeline;		// Geometry Transform Pipeline
    M3DMatrix44f mvpMatrix;    
};
#endif // TUNNELRENDER_H
