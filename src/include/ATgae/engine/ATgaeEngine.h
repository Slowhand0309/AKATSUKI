#ifndef __ATENGINE_H__9224713B_4CDE_5B4C_35F5_71CCC51SS180
#define __ATENGINE_H__9224713B_4CDE_5B4C_35F5_71CCC51SS180
#include "ATgae/engine/com/ATgaeCommon.h"
#include "ATgae/engine/core/ATgaeCore.h"
#include "ATgae/engine/window/ATgaeWindowInfo.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class ATEngine
{
public:

  /**
   * Constructor.
   */
  ATEngine(const EngineType type);

  /**
   * Destructor.
   */
  ~ATEngine();

  /**
   * Initialize engine.
   *
   * @return status code.
   */
  virtual int initialize(int argc, char *argv[]);

  /**
   * Set callback via main loop.
   *
   * @param func Callback
   */
  void setCallback(void(*func)(ATEngine*));

  /**
   * Set window information.
   *
   * @param info ATWindowInfo
   */
  void setWindowInfo(const ATWindowInfo &info);

  /**
   * Run.
   * While loop.
   */
  virtual void run();

  /**
   * Finalize engine.
   *
   * @return status code.
   */
  virtual int finalize();

  /**
   * Execute main logic.
   */
  virtual void execute() = 0;

protected:

  ATLog*        ml_pLog;
  EngineType    ml_nType;
  ATCore*       ml_pCore;
  ATWindowInfo  ml_WindowInfo;
  void(*ml_pCallback)(ATEngine*);
};
#endif // __ATENGINE_H__9224713B_4CDE_5B4C_35F5_71CCC51SS180
