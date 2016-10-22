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

int ATImplGL::initialize(int argc, char *argv[])
{
  int nRet = ATEngine::initialize(argc, argv);

  return nRet;
}

void ATImplGL::run()
{
  ATEngine::run();
}

int ATImplGL::finalize()
{
  int nRet = ATEngine::finalize();

  return nRet;
}

void ATImplGL::execute()
{
  ml_pCallback(this);
  ml_pCore->drawTeapot(); // TODO debug
}
