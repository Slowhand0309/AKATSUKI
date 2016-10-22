#include "ATgae/engine/core/ATgaeCoreGL.h"
#include "ATgae/engine/ATgaeEngineCreator.h"

// global function.
// Call when draw.
void onDraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ATEngine *pEngine = ATEngineCreator::getEngine();
    pEngine->execute();
    glFlush();
}

ATCoreGL::ATCoreGL()
  : ATCore()
{

}

ATCoreGL::~ATCoreGL()
{

}


int ATCoreGL::initialize(int argc, char *argv[])
{
  glutInit(&argc, argv);

  return AT_OK;
}

int ATCoreGL::finalize()
{
  return AT_OK;
}


void ATCoreGL::showWindow(ATWindowInfo &windowInfo)
{
  glutInitWindowSize(windowInfo.getDispWidth(), windowInfo.getDispHeight());
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(windowInfo.getWindowTitle().c_str());
  glutDisplayFunc(onDraw);
  glutMainLoop();
}

void ATCoreGL::drawTeapot()
{
    glutSolidTeapot(0.5);
}

void ATCoreGL::clearScreen(void)
{
  
}
