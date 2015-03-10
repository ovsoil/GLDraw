/*
 * Application.h
 *
 *  Created on: 2015-01-04
 *      Author: ovsoil
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_


#include <GLTools.h>
#include <GLFrustum.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

#include "TrianglesRender.h"
#include "PointTraceRender.h"
#include "TextRender.h"
#include "Singleton.h"
#include "Timer.h"
using OL::LTimer;

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

class Application : public ISingleton<Application>
{
public:
    Application();
    ~Application();

    void Init(int argc, char *argv[]);
    bool Setup();
    void Run();
    
private:
    //静态成员函数作为回调函数
    static void SpecialKeys(int key, int x, int y);
    static void ChangeSize(int w, int h);
    static void Render();
    //静态成员函数中通过该指针访问其它类成员（这只适用与一个类实例的情况，正好Application是单例）
    static Application* pthis;   

    TrianglesRender triangleRender;
    PointTraceRender pointTraceRender;
    TextRender textRender;

    GLMatrixStack		modelViewMatrix;		// Modelview Matrix
    GLMatrixStack		projectionMatrix;		// Projection Matrix
    GLFrustum			viewFrustum;			// View Frustum
    GLGeometryTransform	transformPipeline;		// Geometry Transform Pipeline

    int frame;
    long frameCount;
    LTimer timer;

    friend class ISingleton<Application>;
    friend class auto_ptr<Application>;
};
#endif /* APPLICATION_H_ */
