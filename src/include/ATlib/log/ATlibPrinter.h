#ifndef __ATLIBPRINTER_H__1D62DB63_85E7_4A22_9736_D428BB9C3BE9
#define __ATLIBPRINTER_H__1D62DB63_85E7_4A22_9736_D428BB9C3BE9
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/log/ATlibLogger.h"

#define LOG_LEVEL_UNKOWN_STR "<?>" // Unkown symbol.
#define LOG_LEVEL_INFO_STR   "<I>" // Infomation symbol.
#define LOG_LEVEL_WARN_STR   "<W>" // Warning symbol.
#define LOG_LEVEL_ERROR_STR  "<E>" // Error symbol.
#define LOG_LEVEL_DEBUG_STR  "<D>" // Debug symbol.

// Date time format e.g. 2016/05/06 10:10:30
#define DATE_TIME_FORMAT    "%Y/%m/%d %H:%M:%S"

/**
 * Printer class<br>
 * <b>ATlibPrinter.h</b>
 *
 * @author slowhand0309
 */
class ATPrinter
{
public:
	ATPrinter() {
	};

	virtual ~ATPrinter() {
	};

	virtual void setFile(const TString &fileName) {
	};

	virtual void print(int level, const TString &message) = 0;

protected:

	TString toLevelString(unsigned int level) {
		TString str = LOG_LEVEL_UNKOWN_STR;
		switch(level) {
			case LOG_LEVEL_INFO:
				str = LOG_LEVEL_INFO_STR;
				break;
			case LOG_LEVEL_WARN:
				str = LOG_LEVEL_WARN_STR;
				break;
			case LOG_LEVEL_ERROR:
				str = LOG_LEVEL_ERROR_STR;
				break;
			case LOG_LEVEL_DEBUG:
				str = LOG_LEVEL_DEBUG_STR;
				break;
			default:
				break;
		}
		return str;
	};

};

#endif // __ATLIBPRINTER_H__1D62DB63_85E7_4A22_9736_D428BB9C3BE9
