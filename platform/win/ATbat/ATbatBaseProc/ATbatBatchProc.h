#ifndef __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF
#define __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/utl/ATlibDateUtl.h"
#include "ATlib/log/ATlibLogger.h"
#include "ATlib/log/ATlibSysPrinter.h"

/* argument size max */
#define ARGUMENT_MAX		(4)

/**
 * Logger for batch<br>
 * <b>ATlibBatchProc.h</b>
 *
 * @author slowhand0309
 */
class ATBatchPrinter : public ATPrinter
{
public:

	/**
	 * Constructor.
	 */
	ATBatchPrinter() {};

	/**
	 * Destructor.
	 */
	virtual ~ATBatchPrinter() {
		ml_ofstream.close();
	};

	/**
	 * Set file output.
	 *
	 * @param const TString &fileName file name
	 */
	virtual void setFile(const TString &fileName) {
		ml_ofstream.open(fileName.c_str());
	};

	/**
	 * Print.
	 *
	 * @param int level Log level
	 * @param const TString &message log message
	 */
	virtual void print(int level, const TString &message) {
		TString strLevel;
		switch (level) {
			case LOG_LEVEL_INFO:
				strLevel = _T(" <I> ");
				break;
			case LOG_LEVEL_WARN:
				strLevel = _T(" <W> ");
				break;
			case LOG_LEVEL_ERROR:
				strLevel = _T(" <E> ");
				break;
			case LOG_LEVEL_DEBUG:
				strLevel = _T(" <D> ");
				break;
			default:
				break;
		}

		TString date = ATDateUtl::getCurrentDate();
		tout << date.c_str() << strLevel.c_str() << message.c_str() << std::endl;
		if (ml_ofstream.is_open()) {
			ml_ofstream << date.c_str() << strLevel.c_str() << message.c_str() << std::endl;
		}
	};

private:
	tofstream ml_ofstream;
};

/**
 * Batch proccess class<br>
 * <b>ATlibBatchProc.h</b>
 *
 * @author slowhand0309
 */
class ATBatchProc
{
public:

	/**
	 * Constructor.
	 *
	 * @param const TString &szBatchName batch name
	 */
	ATBatchProc(const TString &szBatchName);

	/**
	 * Destructor.
	 */
	virtual ~ATBatchProc();

	/**
	 * Run.
	 *
	 * @param int argc Argc
	 * @param TCHAR *argv[] Argv
	 * @return int Result
	 */
	virtual int run(int argc, TCHAR *argv[]);

protected:

	/**
	 * initialize
	 *
	 * @return int Result
	 */
	virtual int initialize() = 0;

	/**
	 * Execute
	 *
	 * @return int Result
	 */
	virtual int execute() = 0;

	/**
	 * Finalize
	 */
	virtual void finalize() = 0;

	/**
	 * Split argument.
	 *
	 * @param int argc Argc
	 * @param TCHAR *argv[] Argv
	 * @return int split size
	 */
	virtual int splitArgs(int argc, TCHAR *argv[]);

	/**
	 * Start log.
	 */
	virtual void logAtStart();

	/**
	 * End log.
	 */
	virtual void logAtEnd();

	TString ml_szBatchName;
	TString ml_szExecTime;
	TString ml_szLogPath;
	TString ml_szOutputPath;
	std::vector<TString> ml_vecParam;
	ATLogger<ATBatchPrinter> ml_oLogger;
};
#endif // __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF
