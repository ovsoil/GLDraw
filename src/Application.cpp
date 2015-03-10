#include "Application.h"

Application* Application::pthis = NULL;

Application::Application()
    :frameCount(0)
{

}

Application::~Application()
{

}

///////////////////////////////////////////////////
// Respond to arrow keys, move the viewpoint back
// and forth
void Application::SpecialKeys(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            printf("left\n");
            glutPostRedisplay();
            break;
        case 27:
            printf("exit\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
    // Refresh the Window
}

/////////////////////////////////////////////////////////////////////
// Change viewing volume and viewport.  Called when window is resized
void Application::ChangeSize(int w, int h)
    {
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
    
    pthis = Application::GetSingletonPtr();
    pthis->viewFrustum.SetOrthographic(0, w, 0, h, -1, 1);
    pthis->projectionMatrix.LoadMatrix(pthis->viewFrustum.GetProjectionMatrix());
    pthis->transformPipeline.SetMatrixStacks(pthis->modelViewMatrix, pthis->projectionMatrix);
    }

void Application::Render()
{
    pthis = Application::GetSingletonPtr();

    //if(pthis->frameCount++ == 100)
    //{
    //    double elapsed = pthis->timer.elapsed();
    //    cout << "100 frames: " << elapsed << endl; 
    //    cout << "The FPS is: " << 100.0 / elapsed << endl;
    //    pthis->frameCount = 0;
    //    pthis->timer.restart();
    //}

    static int time, timebase = 0;
    if( pthis->frame == 0 )
    {
        printf(
            "Computing FPS with all scence generation and rendering at each frame...\n" );
        printf(
            "Number of PointTraces(...lines, ...symbol, .. glyphs in a PointTraces): ...\n");
    }

	pthis->frame++;
	time = glutGet( GLUT_ELAPSED_TIME );

    if( time-timebase > (2500) )
    {
        printf( "FPS : %.2f (%d frames in %.2f second)\n",
                pthis->frame*1000.0/(time-timebase), pthis->frame, (time-timebase)/1000.0);
        timebase = time;
        pthis->frame = 0;
    }

    //------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    pthis->modelViewMatrix.PushMatrix();        //保存当前模型视图矩阵（复制栈顶矩阵,用于变换）

    pthis->textRender.SetMVP(pthis->transformPipeline.GetModelViewProjectionMatrix());
    pthis->textRender.Render();
    

    M3DMatrix44f projMatrix;
	m3dMakeOrthographicMatrix(projMatrix, -1, 1, -1, 1, -1, 1);
    pthis->projectionMatrix.PushMatrix(projMatrix);  
    
    //pthis->pointTraceRender.Update();
    pthis->pointTraceRender.SetMVP(pthis->transformPipeline.GetModelViewProjectionMatrix());
    pthis->pointTraceRender.Render();

    //pthis->triangleRender.SetMVP(pthis->transformPipeline.GetModelViewProjectionMatrix());
    //pthis->triangleRender.Render();

    pthis->projectionMatrix.PopMatrix();
    pthis->modelViewMatrix.PopMatrix();
    //---------------------------------------------------------------------------
    glutSwapBuffers();
    glutPostRedisplay();
}

void Application::Init(int argc, char *argv[])
{
    gltSetWorkingDirectory(argv[0]);
    // Standard initialization stuff
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle - mainwindow");
    
    //glewInit()之前要有渲染上下文，这里是新建glut窗口。
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "Status: Using OpenGL %s\n", glewGetString(GL_VERSION));
    
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(Render);
    
}

bool Application::Setup()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
#ifndef GL_TEXTURE_2D
    glEnable(GL_TEXTURE_2D);
#endif
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    triangleRender.SetupRC();
    pointTraceRender.SetupRC();
    textRender.SetupRC();
    return true;
}

void Application::Run()
{
    glutMainLoop();
}
