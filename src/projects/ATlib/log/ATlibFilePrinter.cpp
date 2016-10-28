#include "ATlib/log/ATlibFilePrinter.h"
#include "ATlib/utl/ATlibDateUtl.h"

// Constructor.
ATFilePrinter::ATFilePrinter()
  : ATPrinter()
{
}

// Destructor.
ATFilePrinter::~ATFilePrinter()
{
  ml_File.close();
}

// Set log file.
void ATFilePrinter::setFile(const TString &fileName)
{
  ml_File.open(fileName, OpenMode::OpenMode_TxtWrite);
}

// Print log to file.
void ATFilePrinter::print(int level, const TString &message)
{
  if (ml_File.isOpen()) {
    // Current date.
    TString date = ATDateUtl::getCurrentDate();
    // Level.
    TString levelString = toLevelString(level);

    ml_File.write(_T("%s %s %s"), date.c_str(), levelString.c_str(), message.c_str());
  }
}
