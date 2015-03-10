/*
 * RenderBase.h
 *
 *  Created on: 2015-01-08
 *      Author: ovsoil
 */

#ifndef RENDERBASE_H
#define RENDERBASE_H

class RenderBase
{
public:
    RenderBase();
    ~RenderBase();

    virtual void SetupRC() = 0;
    virtual void CleanRC();
    virtual void Render() = 0;
};

#endif // RENDERBASE_H
