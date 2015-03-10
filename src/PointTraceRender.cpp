/*
 * PointtraceRender.cpp
 *
 *  Created on: 2014-01-08
 *      Author: ovsoil
 */

#include "PointTraceRender.h"
#include "Data.h"

PointTraceRender::PointTraceRender()
    :num(0)
    //,texture("resources/symbol.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE)
    //,texture("/home/ovsoil/img.png", SYMBOL_TYPE_COUNT *  SymbolSize, SYMBOL_COLOR_COUNT * SymbolSize)
{
}

PointTraceRender::~PointTraceRender()
{
    delete[] vVerts_brow;
    delete[] vVerts_symbol;
    delete[] vTexCoords;
}

void PointTraceRender::SetupRC()
{

    // Init ShaderPrograms
    initPrograms();
    // Load textures;
    initTextures();

    num = PointTraceContainer::GetSingleton().elems.size();
    vVerts_brow = new M3DVector3f[2 * num];
    vVerts_symbol = new M3DVector3f[4 * num];
    vTexCoords = new M3DVector2f[4 * num];
    for(int i = 0; i < num; ++i)
    {
        PointTrace pt = PointTraceContainer::GetSingleton().elems[i];
        GLfloat x = pt.pos[0];
        GLfloat y = pt.pos[1];
        GLfloat range = pt.range;
        int type = pt.type;
        int color = pt.color;
        GLfloat size = pt.size * 0.01;  //TODO:

#define ASSIGN_VEC3(VEC3, x, y, z) \
        VEC3[0] = x;\
        VEC3[1] = y;\
        VEC3[2] = z

        ASSIGN_VEC3(vVerts_brow[2 * i + 0], x - range, y, 0.0);
        ASSIGN_VEC3(vVerts_brow[2 * i + 1], x + range, y, 0.0);

        ASSIGN_VEC3(vVerts_symbol[4 * i + 0], x - size/2, y - size/2, 0.0);
        ASSIGN_VEC3(vVerts_symbol[4 * i + 1], x + size/2, y - size/2, 0.0);
        ASSIGN_VEC3(vVerts_symbol[4 * i + 2], x + size/2, y + size/2, 0.0);
        ASSIGN_VEC3(vVerts_symbol[4 * i + 3], x - size/2, y + size/2, 0.0);

        GLfloat x0 = (GLfloat)type * 32 / (SymbolSize* SYMBOL_TYPE_COUNT); //texture.Width();
        GLfloat y0 = (GLfloat)color * 32 / (SymbolSize* SYMBOL_COLOR_COUNT);//texture.Height();
        GLfloat dx = (GLfloat)SymbolSize / (SymbolSize* SYMBOL_TYPE_COUNT); //texture.Width();
        GLfloat dy = (GLfloat)SymbolSize / (SymbolSize* SYMBOL_COLOR_COUNT); //texture.Height();

#define ASSIGN_VEC2(VEC3, x, y) \
        VEC3[0] = x;\
        VEC3[1] = y

        ASSIGN_VEC2(vTexCoords[4 * i + 0], x0, y0);
        ASSIGN_VEC2(vTexCoords[4 * i + 1], x0 + dx, y0);
        ASSIGN_VEC2(vTexCoords[4 * i + 2], x0 + dx, y0 + dy);
        ASSIGN_VEC2(vTexCoords[4 * i + 3], x0, y0 + dy);
    }

    browBatch.Begin(GL_LINES, num * 2);
    browBatch.CopyVertexData3f((GLfloat *)vVerts_brow);
    browBatch.End();

    symbolBatch.Begin(GL_QUADS, num * 4, 1);
    symbolBatch.CopyVertexData3f((GLfloat *)vVerts_symbol);
    symbolBatch.CopyTexCoordData2f((GLfloat *)vTexCoords, 0);
    symbolBatch.End();
}

void PointTraceRender::Update()
{
    browBatch.Begin(GL_LINES, num * 2);
    browBatch.CopyVertexData3f((GLfloat *)vVerts_brow);
    browBatch.End();

    symbolBatch.Begin(GL_QUADS, num * 4, 1);
    symbolBatch.CopyVertexData3f((GLfloat *)vVerts_symbol);
    symbolBatch.CopyTexCoordData2f((GLfloat *)vTexCoords, 0);
    symbolBatch.End();
}

void PointTraceRender::CleanRC()
{

}

void PointTraceRender::SetMVP(const M3DMatrix44f mvp)
{
    memcpy(mvpMatrix, mvp, sizeof(M3DMatrix44f));
}

void PointTraceRender::Render()
{
	glUseProgram(programs[PROGRAM_BROW]);
    GLint iTransform = glGetUniformLocation(programs[PROGRAM_BROW], "mvpMatrix");
	glUniformMatrix4fv(iTransform, 1, GL_FALSE, mvpMatrix);

    glLineWidth(2);
    browBatch.Draw();

    glUseProgram(programs[PROGRAM_SYMBOL]);
    iTransform = glGetUniformLocation(programs[PROGRAM_SYMBOL], "mvpMatrix");
	glUniformMatrix4fv(iTransform, 1, GL_FALSE, mvpMatrix);
    GLint iTextureUniform = glGetUniformLocation(programs[PROGRAM_SYMBOL], "textureUnit");
	glUniform1i(iTextureUniform, 0);

    //texture.Bind();
    TexturesManager::GetSingletonPtr()->GetTexture(TextureName[0])->Bind();
    symbolBatch.Draw();
}
