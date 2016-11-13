#include "ATgae/engine/core/ATgaeCoreGL.h"
#include "ATgae/engine/ATgaeEngineCreator.h"


ATCoreGL::ATCoreGL()
  : ATCore()
{
  ml_pWindow = NULL;
}

ATCoreGL::~ATCoreGL()
{
  ml_pWindow = NULL;
}


int ATCoreGL::initialize(int argc, char *argv[])
{
  if (!glfwInit()) {
    return AT_ERR_OPENGL_INIT;
  }
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

  ml_pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(ml_pWindow);
  // Set input mode: default keyboard
  glfwSetInputMode(ml_pWindow, GLFW_STICKY_KEYS, GL_TRUE);
}

/**
 * Main loop.
 *
 * @param func Callback function.
 */
void ATCoreGL::mainLoop(void(*func)())
{
  while (glfwGetKey(ml_pWindow, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
      !glfwWindowShouldClose(ml_pWindow))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    func();

    glfwSwapBuffers(ml_pWindow);
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
