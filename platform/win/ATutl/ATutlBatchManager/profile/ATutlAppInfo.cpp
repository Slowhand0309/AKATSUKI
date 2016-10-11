#include "stdafx.h"
#include "ATutlAppInfo.h"

#include "ATlib/utl/ATlibStringUtl.h"

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATAppInfo::ATAppInfo()
{
}

//********************************************************************************************
/**
 * コピーコンストラクタ
 *
 * @param	const ATAppInfo &obj		コピー元.
 *
 */
//********************************************************************************************
ATAppInfo::ATAppInfo(const ATAppInfo &obj)
{
	ml_szAppName = obj.ml_szAppName;
	ml_szExplain = obj.ml_szExplain;
	ml_oOptionMap = obj.ml_oOptionMap;
}

//********************************************************************************************
/**
 * デストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATAppInfo::~ATAppInfo()
{
}

//********************************************************************************************
/**
 * アプリケーション名取得
 *
 * @return	TString					アプリ名
 */
//********************************************************************************************
TString ATAppInfo::getName() const
{
	return ml_szAppName;
}

//********************************************************************************************
/**
 * アプリケーション詳細取得
 *
 * @return	TString					詳細
 */
//********************************************************************************************
TString ATAppInfo::getExplain() const
{
	return ml_szExplain;
}

//********************************************************************************************
/**
 * アプリケーション名設定
 *
 * @param	const TString &szName	アプリ名
 */
//********************************************************************************************
void ATAppInfo::setName(const TString &szName)
{
	ml_szAppName = szName;
}

//********************************************************************************************
/**
 * アプリケーション詳細設定
 *
 * @param	const TString &szExplain	詳細
 */
//********************************************************************************************
void ATAppInfo::setExplain(const TString &szExplain)
{
	ml_szExplain = szExplain;
}

//********************************************************************************************
/**
 * オプションパラメータ追加
 *
 * @param	const TString &szName		オプション名
 * @param	const TString &szExplain	詳細
 */
//********************************************************************************************
void ATAppInfo::addOption(const TString &szName, const TString &szExplain)
{
	ml_oOptionMap.insert(ATAppOptionMap::value_type(szName, szExplain));
}

//********************************************************************************************
/**
 * オプションパラメータリスト取得
 *
 * @param	std::list<TString> &optionList			リスト
 * @return	int
 */
//********************************************************************************************
int ATAppInfo::getOptionList(std::list<TString> &optionList)
{
	if (ml_oOptionMap.size() == 0) {
		/* オプションパラメータ無し		*/
		return AT_ERR_NOTFOUND;
	}

	ATAppOptionMap::iterator it;
	for (it = ml_oOptionMap.begin(); it != ml_oOptionMap.end(); ++it) {
		if (ATStringUtl::isNotEmpty(it->first)) {
			optionList.push_back(it->first);
		}
	}
	return AT_OK;
}

//********************************************************************************************
/**
 * オプションパラメータ詳細の取得
 *
 * @param	const TString &optionName		オプションパラメータ名
 * @return	TString							詳細
 */
//********************************************************************************************
TString ATAppInfo::getOptionExplain(const TString &optionName)
{
	if (ATStringUtl::isNotEmpty(optionName)) {
		ATAppOptionMap::iterator it = ml_oOptionMap.find(optionName);
		if (it != ml_oOptionMap.end()) {
			return it->second;
		}
	}
	return AT_EMPTY_STR;
}

//********************************************************************************************
/**
 * オプションパラメータ有無取得
 *
 * @return	bool		true	: あり
 *						false	: なし
 */
//********************************************************************************************
bool ATAppInfo::hasOptionParams() const
{
	return !ml_oOptionMap.empty();
}