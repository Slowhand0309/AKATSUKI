#ifndef __ATGAELOGGER_H__
#define __ATGAELOGGER_H__
#include "ATlib/log/ATlibLogger.h"
#include "ATlib/log/ATlibSysPrinter.h"

class ATLog
{
public:

  // Get ATLog instance.
  static ATLog *getInstance();

  // Release ATLog instance.
  static void Release();
private:

  // Constructor.
  ATLog();

  // Destructor.
  ~ATLog();

  // Logger
  ATLogger<ATSysPrinter> ml_Logger;

  // Instance.
  static ATLog *m_pInstance;
};
#endif // __ATGAELOGGER_H__
