#include "ATgae/engine/core/ATgaeCoreGL.h"


ATCoreGL::ATCoreGL()
  : ATCore()
{

}

ATCoreGL::~ATCoreGL()
{

}

// TODO debug
void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(0.5);
    glFlush();
}

int ATCoreGL::initialize(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(600,600);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow("Wire_teapot");
  glutDisplayFunc(draw);
  return AT_OK;
}

int ATCoreGL::finalize()
{
  return AT_OK;
}


void ATCoreGL::showWindow()
{
  glutMainLoop();
}

void ATCoreGL::clearScreen()
{
  
}
