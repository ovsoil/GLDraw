// main.cpp
#include "TriangleRender.h"
#include "PointRender.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

static TriangleRender render;
static PointRender render2;
///////////////////////////////////////////////////
// Respond to arrow keys, move the viewpoint back
// and forth
void SpecialKeys(int key, int x, int y)
	{
        if(key == 27)
        {
            exit(0);
        }
	if(key == GLUT_KEY_LEFT)
    {
        printf("saf\n");
    }
	// Refresh the Window
	glutPostRedisplay();
	}

/////////////////////////////////////////////////////////////////////
// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
    {
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
    }

void Render()
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    render.Render();
    render2.Render();
    glutSwapBuffers();
}

//////////////////////////////////////////////////////
// Program entry point
int main(int argc, char *argv[])
    {
    gltSetWorkingDirectory(argv[0]);

    // Standard initialization stuff
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle - mainwindow");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(Render);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
        
    // Startup, loop, shutdown
    render.SetupRC();
    render2.SetupRC();
    glutMainLoop();
    
    return 0;
    }
