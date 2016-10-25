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

// Constructor.
ATLog::ATLog()
{
}

// Destructor.
ATLog::~ATLog()
{
}
