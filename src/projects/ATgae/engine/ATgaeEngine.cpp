
#include "ATgae/engine/ATgaeEngine.h"

/**
 * Constructor.
 */
ATEngine::ATEngine(const EngineType type)
{
  ml_nType = type;
}

/**
 * Destructor.
 */
ATEngine::~ATEngine()
{

}

/**
 * Initialize engine.
 *
 * @return status code.
 */
int ATEngine::initialize()
{
  return AT_OK;
}

/**
 * Run.
 * While loop.
 */
void ATEngine::run()
{

}

/**
 * Finalize engine.
 *
 * @return status code.
 */
int ATEngine::finalize()
{
  return AT_OK;
}
