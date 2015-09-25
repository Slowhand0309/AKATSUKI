#ifndef __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1
#define __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1
#include "ATlib/com/ATlibCommon.h"

#define LOG_LEVEL_NONE				(0x00000000)	/* ログ出力無し			*/
#define LOG_LEVEL_INFO				(0x00000001)	/* 情報ログ出力			*/
#define LOG_LEVEL_WARN				(0x00000010)	/* 警告ログ出力			*/
#define LOG_LEVEL_ERROR				(0x00000100)	/* エラーログ出力		*/
#define LOG_LEVEL_DEBUG				(0x00001000)	/* デバッグログ出力		*/

#define LOG_LEVEL	(LOG_LEVEL_INFO | LOG_LEVEL_WARN | LOG_LEVEL_ERROR)

/**
 * ログクラス<br>
 * <b>ATlibLogger.h</b>
 *
 * @author slowhand0309
 */
template <class __Printer>
class ATLogger
{
public:
	/**
	 * コンストラクタ<br>
	 * デフォルトのログ出力レベル
	 *  INFO , WARN, ERROR
	 */
	ATLogger() {
		ml_nLevel = LOG_LEVEL;
	};

	/**
	 * デストラクタ
	 */
	virtual ~ATLogger() {
	};

	/**
	 * ログ出力レベルの設定
	 *
	 * @param int level			出力レベル
	 */
	void setLevel(int level) {
		ml_nLevel = level;
	};

	/**
	 * ファイル設定
	 * 使用する場合のみPrinterで要実装
	 *
	 * @param	const TString &fileName	ファイル名
	 */
	void setFile(const TString &fileName) {
		ml_oPrinter.setFile(fileName);
	};

	/**
	 * ログ出力
	 *
	 * @param	int level				ログ出力レベル
	 * @param	const TString &message	ログ文字列
	 */
	 void log(int level, const TString &message) {
	
		if (checkLevel(level)) {
			ml_oPrinter.print(level, message);
		}
	};

private:

	/**
	 * ログ出力レベルチェック
	 *
	 * @param int level		チェック対象値
	 */
	bool checkLevel(int level) {
		if (ml_nLevel & level) {
			return true;
		}
		return false;
	};

	int				ml_nLevel;
	__Printer		ml_oPrinter;
};
#endif // __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1