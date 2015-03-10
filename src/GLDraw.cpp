// main.cpp
#include "Application.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

//////////////////////////////////////////////////////
// Program entry point
int main(int argc, char *argv[])
{
    //由于App包含Render类，Render类包含GLTexture类，实例化App类之前要glewInit();
    Application *pApp = Application::GetSingletonPtr();
    pApp->Init(argc, argv);
    if(!pApp->Setup())
    {
        cout << "Setup failed!" << endl;
        return 1;
    }
    pApp->Run();
    return 0;
}
