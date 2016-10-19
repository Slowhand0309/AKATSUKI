#ifndef __ATGAECOREGL_H__
#define __ATGAECOREGL_H__
#include "ATgae/engine/core/ATgaeCore.h"

#if defined(PLATFORM_IOS) || defined(PLATFORM_MACOS)
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
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
  virtual int initialize();

  /**
   * Finalize.
   *
   * @return status code.
   */
  virtual int finalize();

  /**
   * Clear screen.
   */
  virtual void clearScreen();
};
#endif // __ATGAECOREGL_H__
