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
  LOGI(_T("ATCoreGL::initialize()"));
  if (!glfwInit()) {
    LOGE(_T("ATCoreGL::initialize() glfwInit error."));
    return AT_ERR_OPENGL_INIT;
  }
  return AT_OK;
}

int ATCoreGL::finalize()
{
  LOGI(_T("ATCoreGL::finalize()"));
  glfwTerminate();
  return AT_OK;
}

/**
 * Show window.
 *
 * @param windowInfo Window info class.
 */
void ATCoreGL::showWindow(ATWindowInfo &windowInfo)
{
  unsigned int width = windowInfo.getWidth();
  unsigned int height = windowInfo.getHeight();
  TString title = windowInfo.getWindowTitle();

  LOGD(_T("Window size: width[%d] height[%d]"), width, height);
  LOGD(_T("Window title: [%s]"), title.c_str());

  ml_pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(ml_pWindow);

  glfwSwapInterval(1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);

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
  LOGI(_T("Start main loop..."));
  while (glfwGetKey(ml_pWindow, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
      !glfwWindowShouldClose(ml_pWindow))
  {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    func();

    // TODO debug
    ATVector2 start2(180.0f, 200.0f);
    ATVector2 end2(180.0f, 300.0f);
    drawLine(start2, end2, ATCOLOR_RED);

    glfwSwapBuffers(ml_pWindow);
    glfwPollEvents();
  }
  LOGI(_T("Finished main loop."));
}


void ATCoreGL::drawTeapot()
{
    //glutSolidTeapot(0.5);
}

void ATCoreGL::clearScreen(void)
{

}
