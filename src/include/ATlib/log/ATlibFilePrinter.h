#ifndef __ATLIBFILEPRINTER_H__
#define __ATLIBFILEPRINTER_H__
#include "ATlib/log/ATlibPrinter.h"
#include "ATlib/io/ATlibFile.h"

/**
 * File Printer class<br>
 * <b>ATlibFilePrinter.h</b>
 *
 * @author slowhand0309
 */
class ATFilePrinter : public ATPrinter
{
public:
  // Constructor.
	ATFilePrinter();

  // Destructor.
	virtual ~ATFilePrinter();

  // Set log file.
  virtual void setFile(const TString &fileName);

  // Print log to file.
	virtual void print(int level, const TString &message);

private:
  ATFile ml_File;
};
#endif // __ATLIBFILEPRINTER_H__
