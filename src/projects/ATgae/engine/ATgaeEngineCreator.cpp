#include "ATgae/engine/ATgaeEngineCreator.h"
#include "ATgae/engine/impl/ATgaeImplGL.h"

ATEngine *ATEngineCreator::pEngine = NULL;

ATEngine *ATEngineCreator::getEngine()
{
  // TODO debug
  if (ATEngineCreator::pEngine == NULL) {
      ATEngineCreator::pEngine = new ATImplGL();
  }
  return ATEngineCreator::pEngine;
}
