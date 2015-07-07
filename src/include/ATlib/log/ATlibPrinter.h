#ifndef __ATLIBPRINTER_H__1D62DB63_85E7_4A22_9736_D428BB9C3BE9
#define __ATLIBPRINTER_H__1D62DB63_85E7_4A22_9736_D428BB9C3BE9
#include "ATlib/com/ATlibCommon.h"

class ATPrinter
{
public:
	ATPrinter() {
	};

	virtual ~ATPrinter() {
	};

	virtual void setFile(const TString &fileName) {
	};

	virtual void print(int level, const TString &message) = 0; // TODO arg
};

#endif // __ATLIBPRINTER_H__1D62DB63_85E7_4A22_9736_D428BB9C3BE9
