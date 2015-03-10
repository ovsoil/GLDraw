/*
 * PointRender.h
 *
 *  Created on: 2014-12-31
 *      Author: ovsoil
 */

#ifndef POINTRENDER_H_
#define POINTRENDER_H_

#include <GLTools.h>
#include <GLShaderManager.h>

class PointRender
{
public:
    PointRender();
    ~PointRender();

    void SetupRC();
    void CleanRC();
    void Render();
private:
    inline void initPrograms();
    GLBatch  pointBatch;

public:
    GLShaderManager		shaderManager;			// Shader Manager
};

#endif /* POINTRENDER_H_ */
