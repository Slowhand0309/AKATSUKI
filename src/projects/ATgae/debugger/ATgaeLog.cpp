#include "ATgae/debugger/ATgaeLog.h"

ATLog *ATLog::m_pInstance = NULL;

// Get ATLog instance.
ATLog *ATLog::getInstance()
{
  if (ATLog::m_pInstance == NULL) {
    ATLog::m_pInstance = new ATLog();
  }
  return ATLog::m_pInstance;
}

// Release ATLog instance.
void ATLog::Release()
{
  if (ATLog::m_pInstance != NULL) {
    AT_SAFE_DELETE(ATLog::m_pInstance);
  }
}

// Set log file.
void ATLog::setFileName(const TString &logFile)
{
  ml_Logger.setFile(logFile);
}

// Log out.
void ATLog::log(int level, const TString &message, ...)
{
  TCHAR dest[_MAX_PATH] = {0};
  va_list args;
  va_start(args, message.size());
  _vstprintf(dest, message.c_str(), args);
  va_end(args);

  ml_Logger.log(level, TString(dest));
}

// Constructor.
ATLog::ATLog()
{
  ml_Logger.setFile(DEFAULT_LOGFILE);
}

// Destructor.
ATLog::~ATLog()
{
}
