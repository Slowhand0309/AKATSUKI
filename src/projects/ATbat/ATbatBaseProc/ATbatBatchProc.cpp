/**
 * バッチ処理基底実装<br>
 * <b>ATbatBatchProc.cpp</b>
 *
 * @author slowhand0309
 */
#include <algorithm>
#include <iterator>
#include "ATbat/base/ATbatBatchProc.h"
#include "ATlib/utl/ATlibSysUtl.h"
#include "ATlib/utl/ATlibStringUtl.h"

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param	const TString &szBatchName		バッチ名
 */
//********************************************************************************************
ATBatchProc::ATBatchProc(const TString &szBatchName)
	: ml_szBatchName(szBatchName)
{
	_tsetlocale(LC_ALL, _T("Japanese"));
}

//********************************************************************************************
/**
 * デストラクタ
 */
//********************************************************************************************
ATBatchProc::~ATBatchProc()
{
}

//********************************************************************************************
/**
 * バッチ実行
 *
 * @param	int argc			引数の数
 * @param	TCHAR *argv[]		引数
 * @return	int
 */
//********************************************************************************************
int ATBatchProc::run(int argc, TCHAR *argv[])
{
	int		nRet = -1;
	TString	szBuff;

	do {
		/* パラメータ解析			*/
		nRet = splitArgs(argc, argv);
		if (nRet < 0) {
			break;
		}

		logAtStart();

		/* 初期化処理				*/
		nRet = initialize();
		if (nRet != AT_OK) {
			/* 初期化NG					*/
			break;
		}

		/* 実行処理					*/
		nRet = execute();

		/* 終了処理			*/
		finalize();

	} while (0);

	logAtEnd();
	return nRet;
}

//********************************************************************************************
/**
 * 引数パラメータの解析
 *  引数
 *     1 : 実行時間 YYYYMMDD_HHMMSS (基底クラスで使用)
 *     2 : ログ出力先
 *     3 : 実行時のファイル等の出力先
 *     4 : 移行のパラメータは継承先で利用
 *
 */
//********************************************************************************************
int ATBatchProc::splitArgs(int argc, TCHAR *argv[])
{
	if (argc <= (ARGUMENT_MAX - 1)) {
		tout << _T("argument error!!.") << std::endl;
		return AT_ERR_ARGUMENTS;
	}

	/* 実行時間の取得			*/
	ml_szExecTime = argv[1];
	if (ml_szExecTime.empty()) {
		tout << _T("exec time empty!!.") << std::endl;
	}
	
	/* ログ出力先の取得			*/
	ml_szLogPath = argv[2];
	if (ATStringUtl::isEmpty(ml_szLogPath)) {
		/* 未設定の場合は実行モジュール直下のパスを設定		*/
		ml_szLogPath = ATSysUtl::getCurrentPath();
	}

	/* 実行時出力先の取得		*/
	ml_szOutputPath = argv[3];
	if (ATStringUtl::isEmpty(ml_szOutputPath)) {
		/* 未設定の場合は実行モジュール直下のパスを設定		*/
		ml_szOutputPath = ATSysUtl::getCurrentPath();
	}

	/* パラメータの取得			*/
	for (int ii = ARGUMENT_MAX; ii < argc; ii++) {
		ml_vecParam.push_back(TString(argv[ii]));
	}

	return ml_vecParam.size();
}

//********************************************************************************************
/**
 * バッチ処理開始時ログ
 */
//********************************************************************************************
void ATBatchProc::logAtStart()
{
	/* 出力ログファイル名生成		*/
	TString file = ml_szLogPath + _T("\\") + ml_szBatchName + _T("_") + ml_szExecTime + _T(".log");
	ml_oLogger.setFile(file);

	TString msg = _T("============= batch start [") + ml_szBatchName + _T("] =============");
	ml_oLogger.log(LOG_LEVEL_INFO, msg);

	/* 開始時刻ログ出力			*/
	TString execTime =  _T("exec time ==> ") + ml_szExecTime;
	ml_oLogger.log(LOG_LEVEL_INFO, execTime);

	/* ログ出力先				*/
	TString logPath = _T("log path ==> ") + file;
	ml_oLogger.log(LOG_LEVEL_INFO, logPath);

	/* 実行時出力パス			*/
	TString outPath = _T("output path ==> ") + ml_szOutputPath;
	ml_oLogger.log(LOG_LEVEL_INFO, outPath);

	/* パラメータログ出力		*/
	TString args = _T("parameters ==> ");
	std::vector<TString>::iterator it;
	for (it = ml_vecParam.begin(); it != ml_vecParam.end(); ++it)
	{
		args += *it + _T(", ");
	}
	ml_oLogger.log(LOG_LEVEL_INFO, args);
}

//********************************************************************************************
/**
 * バッチ終了時ログ
 */
//********************************************************************************************
void ATBatchProc::logAtEnd()
{
	ml_oLogger.log(LOG_LEVEL_INFO, _T("============= batch end ============="));
}