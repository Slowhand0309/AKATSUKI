#include "ATgae/engine/ATgaeEngineCreator.h"
#include "ATgae/engine/impl/ATgaeImplGL.h"

ATEngine *ATEngineCreator::pEngine = NULL;

ATEngine *ATEngineCreator::getEngine()
{
  LOGI(_T("ATEngineCreator::getEngine()"));
  // TODO debug
  if (ATEngineCreator::pEngine == NULL) {
      ATEngineCreator::pEngine = new ATImplGL();
  }
  return ATEngineCreator::pEngine;
}

void ATEngineCreator::releaseEngine()
{
  LOGI(_T("ATEngineCreator::releaseEngine()"));
  
  if (ATEngineCreator::pEngine != NULL) {
    ATEngineCreator::pEngine->finalize();
    AT_SAFE_DELETE(ATEngineCreator::pEngine);
  }
  ATLog::Release();
}
