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

// Call when hit keyboard.
void onKeyboard(unsigned char key , int x , int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;

        default:
            break;
    }
}

void onSpecialKeyboard(int key, int x, int y)
{

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
  glfwInit();

  return AT_OK;
}

int ATCoreGL::finalize()
{
  glfwTerminate();
  return AT_OK;
}


void ATCoreGL::showWindow(ATWindowInfo &windowInfo)
{
  unsigned int width = windowInfo.getWidth();
  unsigned int height = windowInfo.getHeight();
  TString title = windowInfo.getWindowTitle();

  GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    ATEngine *pEngine = ATEngineCreator::getEngine();
    pEngine->execute();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void ATCoreGL::drawTeapot()
{
    //glutSolidTeapot(0.5);
}

void ATCoreGL::clearScreen(void)
{

}
