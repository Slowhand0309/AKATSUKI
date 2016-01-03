#ifndef __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1
#define __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1
#include "ATlib/com/ATlibCommon.h"

#define LOG_LEVEL_NONE        (0x00000000) /* Not print log */
#define LOG_LEVEL_INFO        (0x00000001) /* Print infomation log */
#define LOG_LEVEL_WARN        (0x00000010) /* Print warning log */
#define LOG_LEVEL_ERROR       (0x00000100) /* Print error log */
#define LOG_LEVEL_DEBUG       (0x00001000) /* Print debug log */

#define LOG_LEVEL	(LOG_LEVEL_INFO | LOG_LEVEL_WARN | LOG_LEVEL_ERROR)

/**
 * Log class<br>
 * <b>ATlibLogger.h</b>
 *
 * @author slowhand0309
 */
template <class __Printer>
class ATLogger
{
public:
	/**
	 * Constructor<br>
	 * Default level print<br>
	 *  INFO , WARN, ERROR
	 */
	ATLogger() {
		ml_nLevel = LOG_LEVEL;
	};

	/**
	 * Destructor
	 */
	virtual ~ATLogger() {
	};

	/**
	 * Set log level
	 *
	 * @param int level Log level
	 */
	void setLevel(int level) {
		ml_nLevel = level;
	};

	/**
	 * Set filename<br>
	 * Need implements Printer if use file.
	 *
	 * @param	const TString &fileName FileName
	 */
	void setFile(const TString &fileName) {
		ml_oPrinter.setFile(fileName);
	};

	/**
	 * Print log.
	 *
	 * @param	int level Log level
	 * @param	const TString &message Log message
	 */
	 void log(int level, const TString &message) {

		if (checkLevel(level)) {
			ml_oPrinter.print(level, message);
		}
	};

private:

	/**
	 * Check for level
	 *
	 * @param int level Log level
	 */
	bool checkLevel(int level) {
		if (ml_nLevel & level) {
			return true;
		}
		return false;
	};

	int ml_nLevel;
	__Printer ml_oPrinter;
};
#endif // __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1
