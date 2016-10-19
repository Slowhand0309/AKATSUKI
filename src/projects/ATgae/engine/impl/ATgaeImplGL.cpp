#include "ATgae/engine/impl/ATgaeImplGL.h"

/**
 * Constructor.
 */
ATImplGL::ATImplGL()
  : ATEngine(EngineType_OpenGL)
{

}

/**
 * Destructor.
 */
ATImplGL::~ATImplGL()
{

}

int ATImplGL::initialize()
{
  int nRet = ATEngine::initialize();

  return nRet;
}

int ATImplGL::finalize()
{
  int nRet = ATEngine::finalize();

  return nRet;
}
