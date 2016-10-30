#ifndef __ATGAELOGGER_H__
#define __ATGAELOGGER_H__
#include "ATlib/log/ATlibLogger.h"

#define LOG_FILE

#if defined(LOG_SYSTEM)
#include "ATlib/log/ATlibSysPrinter.h"
#define ATPRINTER          ATSysPrinter

#elif defined(LOG_FILE)
#include "ATlib/log/ATlibFilePrinter.h"
#define ATPRINTER          ATFilePrinter

#endif

// Default log file name. (No effect in sysprinter)
#define DEFAULT_LOGFILE    _T("AT.log")


class ATLog
{
public:

  // Get ATLog instance.
  static ATLog *getInstance();

  // Release ATLog instance.
  static void Release();

  // Set log file name.
  void setFileName(const TString &logFile);

  // Log out.
  void log(int level, const TString &message);
private:

  // Constructor.
  ATLog();

  // Destructor.
  ~ATLog();

  // Logger
  ATLogger<ATPRINTER> ml_Logger;

  // Instance.
  static ATLog *m_pInstance;
};
#endif // __ATGAELOGGER_H__
