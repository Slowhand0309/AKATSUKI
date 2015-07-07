#ifndef __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75
#define __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75

#include "ATlib/com/ATlibCommon.h"
#include "ATlib/utl/ATlibStringUtl.h"
#include <time.h>

#define DEFAULT_DATE_FORMAT			_T("%Y/%m/%d %H:%M:%S")

class ATDateUtl
{
public:

	/**
	 * 現在の日時を文字列で取得
	 *
	 * @return			現在日時
	 */
	static TString getCurrentDate() {
		return getCurrentDate(DEFAULT_DATE_FORMAT);
	};

	/**
	 * 現在の日時を文字列で取得
	 *
	 * @param		TString szFormat	日付フォーマット文字列
	 *
	 * @return		現在日時
	 */
	static TString getCurrentDate(TString szFormat) {

		time_t		lTime;
		struct tm	*tagNow;
		size_t		uiRet = 0;
		TCHAR		szTime[_MAX_PATH] = {0};

		time(&lTime);
		tagNow = localtime(&lTime);

		if (_tcsftime(szTime, _MAX_PATH, szFormat.c_str(), tagNow) == 0) {
			return TString();
		}
		return TString(szTime);
	};

#ifdef PLATFORM_WINDOWS
/* declaration for windows					*/

	/**
	 * 引数のSYSTEMTIMEをフォーマット文字列で取得
	 * 
	 * @param	SYSTEMTIME stSysTime		システムタイム
	 * @param	const TString &szFormat		フォーマット
	 * @return	TString						文字列
	 */
	static TString getFormatString(SYSTEMTIME stSysTime, const TString &szFormat) {

		if (ATStringUtl::isEmpty(szFormat)) {
			return AT_EMPTY_STR;
		}

		TCHAR		szValue[_MAX_PATH] = {0};
		_stprintf(szValue, szFormat.c_str(), 
					stSysTime.wYear,   stSysTime.wMonth,
					stSysTime.wDay,    stSysTime.wHour,
					stSysTime.wMinute, stSysTime.wSecond);

		return TString(szValue);
	}

#endif // PLATFORM_WINDOWS

private:
	/**
	 * インスタンスの作成禁止
	 */
	ATDateUtl();
};
#endif // __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75
