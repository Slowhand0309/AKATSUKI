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

  /**
   * Draw point.
   *
   * @param pointVec2 Point coordinate
   * @param color     Point color
   * @param size      Point size
   */
  virtual void drawPoint(ATVector2 &pointVec2, ATColor color, float size = 1.0f) = 0;

  /**
   * Draw line.
   *
   * @param startVec2  Start coordinate
   * @param endVec2 End coordinate
   * @param color Line color
   * @param lineWidth Line width
   */
  virtual void drawLine(ATVector2 &startVec2, ATVector2 &endVec2, ATColor color, float lineWidth = 1.0f) = 0;

};
#endif // __ATCORE_H__9384714E_12AB_4B7B_A5D5_11B8AA10A189
