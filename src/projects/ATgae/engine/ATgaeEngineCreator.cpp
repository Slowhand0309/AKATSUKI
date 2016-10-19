#include "ATgae/engine/ATgaeEngineCreator.h"
#include "ATgae/engine/impl/ATgaeImplGL.h"

ATEngine *ATEngineCreator::getEngine()
{
  // TODO debug
  return new ATImplGL();
}
