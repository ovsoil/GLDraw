/*
 * PointRender.cpp
 *
 *  Created on: 2014-12-31
 *      Author: ovsoil
 */

#include "PointRender.h"
#include <stdlib.h>
#include <time.h>

PointRender::PointRender()
{
}

PointRender::~PointRender()
{
}

inline void PointRender::initPrograms()
{
    shaderManager.InitializeStockShaders();
}

void PointRender::SetupRC()
{
    // Init ShaderPrograms
    initPrograms();

	srand((int)time(0));
    GLfloat vVerts[30];
    for(int i = 0; i < 10; ++i)
    {
    	vVerts[3 * i] = -0.5 + 1.0 * rand() / RAND_MAX;
    	vVerts[3 * i + 1] = -0.5 + 1.0 * rand() / RAND_MAX;
    	vVerts[3 * i + 2] = 0;
    }
    // Build Geometry
    pointBatch.Begin(GL_POINTS, 10);
    pointBatch.CopyVertexData3f(vVerts);
    pointBatch.End();
}


void PointRender::CleanRC()
{

}

void PointRender::Render()
{
	GLfloat vcolor[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vcolor);
    pointBatch.Draw();
}
