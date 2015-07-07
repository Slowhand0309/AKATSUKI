#ifndef __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF
#define __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/utl/ATlibDateUtl.h"
#include "ATlib/log/ATlibLogger.h"
#include "ATlib/log/ATlibSysPrinter.h"

#define ARGUMENT_MAX		(4)

/**
 * バッチ用Printerクラス<br>
 * <b>ATlibBatchProc.h</b>
 *
 * @author j-fujisaki
 */
class ATBatchPrinter : public ATPrinter
{
public:

	/**
	 * コンストラクタ
	 */
	ATBatchPrinter() {};

	/**
	 * デストラクタ
	 */
	virtual ~ATBatchPrinter() {
		ml_ofstream.close();
	};

	/**
	 * ログファイルの設定
	 *
	 * @param const TString &fileName	ログファイル名
	 */
	virtual void setFile(const TString &fileName) {
		ml_ofstream.open(fileName.c_str());
	};

	/**
	 * ログ出力
	 *
	 * @param int level					ログ出力レベル
	 * @param const TString &message	出力文字列
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
 * バッチ処理基底クラス<br>
 * <b>ATlibBatchProc.h</b>
 *
 * @author j-fujisaki
 */
class ATBatchProc
{
public:

	/**
	 * コンストラクタ
	 *
	 * @param const TString &szBatchName	バッチ名
	 */
	ATBatchProc(const TString &szBatchName);

	/**
	 * デストラクタ
	 */
	virtual ~ATBatchProc();

	/**
	 * バッチ実行
	 *
	 * @param int argc				引数の数
	 * @param TCHAR *argv[]			引数
	 * @return int
	 */
	virtual int run(int argc, TCHAR *argv[]);

protected:

	/**
	 * 初期化処理<br>
	 * 純粋仮想関数
	 *
	 * @return int
	 */
	virtual int initialize() = 0;

	/**
	 * 実行処理<br>
	 * 純粋仮想関数
	 *
	 * @return int
	 */
	virtual int execute() = 0;

	/**
	 * 終了処理<br>
	 * 純粋仮想関数
	 */
	virtual void finalize() = 0;

	/**
	 * 引数解析処理
	 *
	 * @param int argc				引数の数
	 * @param TCHAR *argv[]			引数
	 * @return int					解析後の引数の数
	 */
	virtual int splitArgs(int argc, TCHAR *argv[]);

	/**
	 * バッチ開始時ログ
	 */
	virtual void logAtStart();

	/**
	 * バッチ終了時ログ
	 */
	virtual void logAtEnd();

	TString						ml_szBatchName;
	TString						ml_szExecTime;
	TString						ml_szLogPath;
	TString						ml_szOutputPath;
	std::vector<TString>		ml_vecParam;
	ATLogger<ATBatchPrinter>	ml_oLogger;
};
#endif // __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF