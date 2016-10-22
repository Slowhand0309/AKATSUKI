
#include "ATgae/engine/ATgaeEngine.h"
#include "ATgae/engine/core/ATgaeCoreGL.h"
#include "ATgae/engine/window/ATgaeWindowInfo.h"

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

  return nRet;
}

/**
 * Set callback via main loop.
 *
 * @param func Callback
 */
void ATEngine::setCallback(void(*func)(ATEngine*))
{
  this->ml_pCallback = func;
}

/**
 * Run.
 * While loop.
 */
void ATEngine::run()
{
  // TODO debug
  ATWindowInfo info;
  info.setDispWidth(800);
  info.setDispHeight(500);
  info.setWindowTitle(_T("AKATSUKI"));
  ml_pCore->showWindow(info);
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
