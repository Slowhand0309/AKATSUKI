#ifndef __ATLIBSYSPRINTER_H__1B09F435_5BFB_4CF7_87A1_9EBC84C7B80B
#define __ATLIBSYSPRINTER_H__1B09F435_5BFB_4CF7_87A1_9EBC84C7B80B
#include "ATlib/log/ATlibPrinter.h"

/**
 * システム標準出力クラス<br>
 * <b>ATlibSysPrinter.h</b>
 *
 * @author slowhand0309
 */
class ATSysPrinter : public ATPrinter
{
public:
	ATSysPrinter() {
	};

	virtual ~ATSysPrinter() {
	};

	virtual void print(int level, const TString &message) {
		TRACE(message.c_str());
	};
};
#endif // __ATLIBSYSPRINTER_H__1B09F435_5BFB_4CF7_87A1_9EBC84C7B80B