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
   * Clear screen.
   */
  virtual void clearScreen();

  /**
   * Draw teapot sample.
   */
  virtual void drawTeapot();

};
#endif // __ATGAECOREGL_H__
