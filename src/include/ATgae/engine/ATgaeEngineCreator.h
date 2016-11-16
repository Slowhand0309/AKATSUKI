#ifndef __ATGAEENGINECREATOR_H__
#define __ATGAEENGINECREATOR_H__
#include "ATgae/engine/ATgaeEngine.h"

class ATEngineCreator
{
public:

  // Get engine instance.
  static ATEngine *getEngine();

  // Release engine instance.
  static void releaseEngine();

private:

  static ATEngine *pEngine;
};

#endif // __ATGAEENGINECREATOR_H__
