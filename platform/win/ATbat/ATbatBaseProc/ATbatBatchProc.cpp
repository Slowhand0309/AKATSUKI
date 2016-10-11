/**
 * Implement ATbatBatchProc class<br>
 * <b>ATbatBatchProc.cpp</b>
 *
 * @author slowhand0309
 */
#include <algorithm>
#include <iterator>
#include "ATbatBatchProc.h"
#include "ATlib/utl/ATlibSysUtl.h"
#include "ATlib/utl/ATlibStringUtl.h"

/**
 * Constructor.
 *
 * @param const TString &szBatchName batch name
 */
 ATBatchProc::ATBatchProc(const TString &szBatchName)
	: ml_szBatchName(szBatchName)
{
	_tsetlocale(LC_ALL, _T("Japanese"));
}

/**
 * Destructor.
 */
ATBatchProc::~ATBatchProc()
{
}

/**
 * Run.
 *
 * @param int argc Argc
 * @param TCHAR *argv[] Argv
 * @return int Result
 */
int ATBatchProc::run(int argc, TCHAR *argv[])
{
	int		nRet = -1;
	TString	szBuff;

	do {
		/* split args */
		nRet = splitArgs(argc, argv);
		if (nRet < 0) {
			break;
		}

		logAtStart();

		nRet = initialize();
		if (nRet != AT_OK) {
			/* NG */
			break;
		}

		nRet = execute();

		finalize();

	} while (0);

	logAtEnd();
	return nRet;
}

/**
 * Split argument.
 *
 * @param int argc Argc
 * @param TCHAR *argv[] Argv
 * @return int split size
 */
int ATBatchProc::splitArgs(int argc, TCHAR *argv[])
{
	if (argc <= (ARGUMENT_MAX - 1)) {
		tout << _T("argument error!!.") << std::endl;
		return AT_ERR_ARGUMENTS;
	}

	/* execute time */
	ml_szExecTime = argv[1];
	if (ml_szExecTime.empty()) {
		tout << _T("exec time empty!!.") << std::endl;
	}

	/* log path */
	ml_szLogPath = argv[2];
	if (ATStringUtl::isEmpty(ml_szLogPath)) {
		/* set default path */
		ml_szLogPath = ATSysUtl::getCurrentPath();
	}

	/* output path */
	ml_szOutputPath = argv[3];
	if (ATStringUtl::isEmpty(ml_szOutputPath)) {
		/* set default path */
		ml_szOutputPath = ATSysUtl::getCurrentPath();
	}

	/* batch args */
	for (int ii = ARGUMENT_MAX; ii < argc; ii++) {
		ml_vecParam.push_back(TString(argv[ii]));
	}

	return ml_vecParam.size();
}

/**
 * Start log.
 */
void ATBatchProc::logAtStart()
{
	TString file = ml_szLogPath + _T("\\") + ml_szBatchName + _T("_") + ml_szExecTime + _T(".log");
	ml_oLogger.setFile(file);

	TString msg = _T("============= batch start [") + ml_szBatchName + _T("] =============");
	ml_oLogger.log(LOG_LEVEL_INFO, msg);

	TString execTime =  _T("exec time ==> ") + ml_szExecTime;
	ml_oLogger.log(LOG_LEVEL_INFO, execTime);

	TString logPath = _T("log path ==> ") + file;
	ml_oLogger.log(LOG_LEVEL_INFO, logPath);

	TString outPath = _T("output path ==> ") + ml_szOutputPath;
	ml_oLogger.log(LOG_LEVEL_INFO, outPath);

	TString args = _T("parameters ==> ");
	std::vector<TString>::iterator it;
	for (it = ml_vecParam.begin(); it != ml_vecParam.end(); ++it)
	{
		args += *it + _T(", ");
	}
	ml_oLogger.log(LOG_LEVEL_INFO, args);
}

/**
 * End log.
 */
void ATBatchProc::logAtEnd()
{
	ml_oLogger.log(LOG_LEVEL_INFO, _T("============= batch end ============="));
}
