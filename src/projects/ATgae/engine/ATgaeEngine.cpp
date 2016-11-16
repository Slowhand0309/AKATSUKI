
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
      LOGI(_T("Engine type: OpenGL"));
      ml_pCore = new ATCoreGL();
      break;

    case EngineType_DirectX:
      LOGI(_T("Engine type: DirectX"));
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
  LOGI(_T("ATEngine::initialize argc[%d]"), argc);
  int nRet = ml_pCore->initialize(argc, argv);

  return nRet;
}

/**
 * Set callback via main loop.
 *
 * @param func Callback
 */
void ATEngine::setCallback(void(*func)())
{
  this->ml_pCallback = func;
}

/**
 * Set window information.
 *
 * @param info ATWindowInfo
 */
void ATEngine::setWindowInfo(const ATWindowInfo &info)
{
  ml_WindowInfo = info;
}

/**
 * Run.
 * While loop.
 */
void ATEngine::run()
{
  // Show window.
  ml_pCore->showWindow(ml_WindowInfo);

  // Do main loop.
  ml_pCore->mainLoop(ml_pCallback);
}

/**
 * Finalize engine.
 *
 * @return status code.
 */
int ATEngine::finalize()
{
  LOGI(_T("ATEngine::finalize"));
  return AT_OK;
}
