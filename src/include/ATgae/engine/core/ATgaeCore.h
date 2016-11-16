#ifndef __ATCORE_H__9384714E_12AB_4B7B_A5D5_11B8AA10A189
#define __ATCORE_H__9384714E_12AB_4B7B_A5D5_11B8AA10A189
#include "ATgae/engine/com/ATgaeCommon.h"
#include "ATgae/engine/window/ATgaeWindowInfo.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATCore
{
public:

  /**
   * Constructor.
   */
  ATCore();

  /**
   * Destructor.
   */
  virtual ~ATCore();

  /**
   * Initialize.
   *
   * @return status code.
   */
  virtual int initialize(int argc, char *argv[]) = 0;

  /**
   * Finalize.
   *
   * @return status code.
   */
  virtual int finalize() = 0;

  /**
   * Show main window.
   */
  virtual void showWindow(ATWindowInfo &windowInfo) = 0;

  /**
   * Main loop.
   *
   * @param func Callback function.
   */
  virtual void mainLoop(void(*func)()) = 0;

  /**
   * Clear screen.
   */
  virtual void clearScreen() = 0;

  /**
   * Draw teapot sample.
   */
  virtual void drawTeapot() = 0;

};
#endif // __ATCORE_H__9384714E_12AB_4B7B_A5D5_11B8AA10A189
