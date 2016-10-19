#ifndef __ATGAEIMPLGL_H__
#define __ATGAEIMPLGL_H__
#include "ATgae/engine/ATgaeEngine.h"

class ATImplGL : public ATEngine
{
public:

  /**
   * Constructor.
   */
  ATImplGL();

  /**
   * Destructor.
   */
  ~ATImplGL();

  /**
   * Initialize engine.
   *
   * @return status code.
   */
  virtual int initialize(int argc, char *argv[]);

  /**
   * Run.
   * While loop.
   */
  virtual void run();

  /**
   * Finalize engine.
   *
   * @return status code.
   */
  virtual int finalize();

protected:

  /**
   * Execute main logic.
   */
  virtual void execute();
};

#endif // __ATGAEIMPLGL_H__
