#include "stdafx.h"
#include "ATutlBatchManagerProfile.h"
#include "ATlib/utl/ATlibStringUtl.h"

#define	KEY_APPLICATION			_T("APPLICATION")
#define KEY_BASE_DIR			_T("BASEDIR")
#define KEY_OUT_DIR				_T("OUTDIR")
#define KEY_LOG_DIR				_T("LOGDIR")

#define OPTION_MARK				_T("Option-")
#define OPTION_PARAM_SPLITKEY	_T(",")

#define EXPLAIN_MARK			_T("Explain-")

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATBatchManagerProfile::ATBatchManagerProfile()
	: ATProfile()
{
}

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param	const TString &szFileName		iniファイルパス.
 *
 */
//********************************************************************************************
ATBatchManagerProfile::ATBatchManagerProfile(const TString &szFileName)
	: ATProfile(szFileName)
{
}

//********************************************************************************************
/**
 * デストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATBatchManagerProfile::~ATBatchManagerProfile()
{
}

//********************************************************************************************
/**
 * iniファイル読み込み
 *
 * @param		const TString &szFileName		iniファイルパス.
 * @return		int
 */
//********************************************************************************************
int ATBatchManagerProfile::readProfile(const TString &szFileName)
{
	int nRet = ATProfile::readProfile(szFileName);
	if (nRet == AT_OK) {

		/* アプリケーションリストの取得		*/
		std::list<TString> appNameList;
		nRet = getValues(KEY_APPLICATION, appNameList);
		if (nRet != AT_OK) {
			return nRet;
		}

		std::list<TString>::iterator it;
		for (it = appNameList.begin(); it != appNameList.end(); ++it) {
			ATAppInfo appInfo;
			appInfo.setName((*it));

			/* オプションパラメータ取得		*/
			std::list<TString> optionList;
			TString optionKey = OPTION_MARK + *it;
			int nTemp = getValues(optionKey, optionList);
			if (nTemp == AT_OK) {
				/* オプション文字列分割		*/
				std::list<TString>::iterator iit;
				for (iit = optionList.begin(); iit != optionList.end(); ++iit) {
					std::list<TString> oValues
						= ATStringUtl::split(*iit, TString(OPTION_PARAM_SPLITKEY));
					appInfo.addOption(oValues.front(), oValues.back());
				}
			}

			/* 詳細の取得		*/
			std::list<TString> explainList;
			TString explainKey = EXPLAIN_MARK + *it;
			nTemp = getValues(explainKey, explainList);
			if (nTemp == AT_OK) {
				appInfo.setExplain(explainList.front());
			}

			ml_oAppInfoList.push_back(appInfo);
		}
	}
	return nRet;
}

//********************************************************************************************
/**
 * アプリケーションリストの取得
 *
 * @param			アプリケーションリスト.
 *
 */
//********************************************************************************************
std::list<ATAppInfo> ATBatchManagerProfile::getAppInfoList()
{
	return ml_oAppInfoList;
}

//********************************************************************************************
/**
 * 基準ディレクトリの取得
 *
 * @param	TString		基準ディレクトリ.
 *
 */
//********************************************************************************************
TString ATBatchManagerProfile::getBaseDir()
{
	std::list<TString> list;
	int nRet = getValues(KEY_BASE_DIR, list);
	if (nRet != AT_OK) {
		return AT_EMPTY_STR;
	}

	/* 先頭に設定されているパスのみ採用		*/
	return list.front();
}

//********************************************************************************************
/**
 * ログディレクトリの取得
 *
 * @param	TString		ログディレクトリ.
 *
 */
//********************************************************************************************
TString ATBatchManagerProfile::getLogDir()
{
	std::list<TString> list;
	int nRet = getValues(KEY_LOG_DIR, list);
	if (nRet != AT_OK) {
		return AT_EMPTY_STR;
	}

	/* 先頭に設定されているパスのみ採用		*/
	return list.front();
}

//********************************************************************************************
/**
 * 出力ディレクトリの取得
 *
 * @param	TString		出力ディレクトリ.
 *
 */
//********************************************************************************************
TString ATBatchManagerProfile::getOutputDir()
{
	std::list<TString> list;
	int nRet = getValues(KEY_OUT_DIR, list);
	if (nRet != AT_OK) {
		return AT_EMPTY_STR;
	}

	/* 先頭に設定されているパスのみ採用		*/
	return list.front();
}