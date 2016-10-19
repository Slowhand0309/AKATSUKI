
#include "ATgae/engine/ATgaeEngine.h"
#include "ATgae/engine/core/ATgaeCoreGL.h"

/**
 * Constructor.
 */
ATEngine::ATEngine(const EngineType type)
{
  ml_nType = type;

  // Create core instance.
  switch (ml_nType) {
    case EngineType_OpenGL: // use opengl
      ml_pCore = new ATCoreGL();
      break;

    case EngineType_DirectX:
      break;
  }
}

/**
 * Destructor.
 */
ATEngine::~ATEngine()
{
  AT_SAFE_DELETE(ml_pCore);
}

/**
 * Initialize engine.
 *
 * @return status code.
 */
int ATEngine::initialize(int argc, char *argv[])
{
  int nRet = ml_pCore->initialize(argc, argv);
  ml_pCore->showWindow();
  return nRet;
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
