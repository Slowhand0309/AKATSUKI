#ifndef __ATGAECOREGL_H__
#define __ATGAECOREGL_H__
#include "ATgae/engine/core/ATgaeCore.h"

#if defined(PLATFORM_IOS)
#elif defined(PLATFORM_MACOS)
#include <OpenGL/OpenGL.h>
#include <external/GLFW/glfw3.h>
#else
#endif

class ATCoreGL : public ATCore
{
public:

  /**
   * Constructor.
   */
  ATCoreGL();

  /**
   * Destructor.
   */
  virtual ~ATCoreGL();

  /**
   * Initialize.
   *
   * @return status code.
   */
  virtual int initialize(int argc, char *argv[]);

  /**
   * Finalize.
   *
   * @return status code.
   */
  virtual int finalize();

  /**
   * Show main window.
   */
  virtual void showWindow(ATWindowInfo &windowInfo);

  /**
   * Main loop.
   *
   * @param func Callback function.
   */
  virtual void mainLoop(void(*func)());

  /**
   * Clear screen.
   */
  virtual void clearScreen();

  /**
   * Draw teapot sample.
   */
  virtual void drawTeapot();

private:
  GLFWwindow *ml_pWindow;
  
};
#endif // __ATGAECOREGL_H__
