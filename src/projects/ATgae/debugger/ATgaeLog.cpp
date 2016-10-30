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
void ATLog::log(int level, const TString &message)
{
  ml_Logger.log(level, message);
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
