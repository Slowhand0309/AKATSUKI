#ifndef __ATCORE_H__9384714E_12AB_4B7B_A5D5_11B8AA10A189
#define __ATCORE_H__9384714E_12AB_4B7B_A5D5_11B8AA10A189
#include "ATlib/com/ATlibCommon.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ATCore
{
public:

  /**
   * Constructor.
   */
  ATCore();

  /**
   * Destructor.
   */
  ~ATCore();

  /**
   * Initialize.
   *
   * @return status code.
   */
  virtual int initialize() = 0;

  /**
   * Finalize.
   *
   * @return status code.
   */
  virtual int finalize() = 0;

  /**
   * Clear screen.
   */
  virtual void clearScreen() = 0;
};
#endif // __ATCORE_H__9384714E_12AB_4B7B_A5D5_11B8AA10A189
