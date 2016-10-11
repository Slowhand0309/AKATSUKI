#ifndef __ATWINDOWMANAGER_H__4384714E_4EAB_4B7B_A5D5_11B8B510A189
#define __ATWINDOWMANAGER_H__4384714E_4EAB_4B7B_A5D5_11B8B510A189
#include "ATlib/com/ATlibCommon.h"
#include "ATgae/engine/window/ATgaeWindowInfo.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATgaeWindowManager
{
public:

  /**
   * Constructor.
   */
  ATgaeWindowManager();

  /**
   * Destructor.
   */
  ~ATgaeWindowManager();

  /**
   * Initialize.
   *
   * @param argc
   * @param argv
   */
  void initialize(int argc, TCHAR *argv[]);

  /**
   * Create window.
   *
   * @param windowInfo
   */
  void createWindow(const ATWindowInfo &windowInfo);

};
#endif // __ATWINDOWMANAGER_H__4384714E_4EAB_4B7B_A5D5_11B8B510A189
