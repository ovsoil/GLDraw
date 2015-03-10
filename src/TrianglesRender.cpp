/*
 * TrianglesRender.cpp
 *
 *  Created on: 2014-01-03
 *      Author: ovsoil
 */

#include "TrianglesRender.h"

TrianglesRender::TrianglesRender()
{
}

TrianglesRender::~TrianglesRender()
{
}

void TrianglesRender::SetupRC()
{
    // Init ShaderPrograms
    initPrograms();

    // Init Textures
    initTextures();

	// Load up triangle1
	GLfloat vVerts[] = { -0.6f, 0.0f, 0.0f, 
		                 -0.1f, 0.0f, 0.0f,
						 -0.1f, 0.5f, 0.0f };

	GLfloat vTexCoords[] = {0.0f, 0.0f, 
		                  1.0f, 0.0f,
						  0.5f, 1.0f };

	triangle1.Begin(GL_TRIANGLES, 3, 1);
	triangle1.CopyVertexData3f(vVerts);
    triangle1.CopyTexCoordData2f(vTexCoords, 0);
    triangle1.End();

	// Load up triangle2
	GLfloat vVerts2[] = {  0.6f, 0.0f, 0.0f, 
		                  0.1f, 0.0f, 0.0f,
						  0.1f, 0.5f, 0.0f };

	GLfloat vTexCoords2[] = {0.0f, 0.0f, 
		                  1.0f, 0.0f,
						  0.5f, 1.0f };

	triangle2.Begin(GL_TRIANGLES, 3, 1);
	triangle2.CopyVertexData3f(vVerts2);
    triangle2.CopyTexCoordData2f(vTexCoords2, 0);
    triangle2.End();
    

    triangle3.Begin(GL_TRIANGLES, 3);
    triangle3.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    triangle3.Vertex3f(-0.6f, -0.1f, 0.0f);
    triangle3.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
    triangle3.Vertex3f(0.6f, -0.1f, 0.0f);
    triangle3.Color4f(0.0f, 0.0f, 1.0f, 1.0f);
    triangle3.Vertex3f(0.0f, -0.6f, 0.0f);
	triangle3.End();
}


void TrianglesRender::CleanRC()
{

}

void TrianglesRender::SetMVP(const M3DMatrix44f mvp)
{
    memcpy(mvpMatrix, mvp, sizeof(M3DMatrix44f));
}

void TrianglesRender::Render()
{
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, &mvpMatrix, 0);

    TexturesManager::GetSingletonPtr()->GetTexture("tex1")->Bind();
	triangle1.Draw();

    TexturesManager::GetSingletonPtr()->GetTexture("tex2")->Bind();
    triangle2.Draw();

    triangle3.Draw();
}
