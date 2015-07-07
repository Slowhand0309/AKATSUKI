#ifndef __ATUTLAPPINFO_H__DA2E17D2_3CFD_410F_812D_4D717ECCE339
#define __ATUTLAPPINFO_H__DA2E17D2_3CFD_410F_812D_4D717ECCE339

typedef std::list<TString>			ATAppOptionList;
typedef std::map<TString, TString>	ATAppOptionMap;

/**
 * バッチアプリケーション情報クラス
 * ATAppInfo.h
 *
 * @author	jf-orange
 */
class ATAppInfo
{
public:
	/**
	 * コンストラクタ
	 */
	ATAppInfo();

	/**
	 * コピーコンストラクタ
	 */
	ATAppInfo(const ATAppInfo &obj);

	/**
	 * デストラクタ
	 */
	virtual ~ATAppInfo();

	/**
	 * アプリケーション名の設定
	 *
	 * @param const TString &szName		アプリ名
	 */
	void setName(const TString &szName);

	/**
	 * アプリケーション詳細設定
	 *
	 * @param const TString &szExplain	詳細
	 */
	void setExplain(const TString &szExplain);

	/**
	 * アプリケーション名取得
	 *
	 * @return TString		アプリケーション名
	 */
	TString getName() const;

	/**
	 * アプリケーションの詳細取得
	 *
	 * @return TString		詳細
	 */
	TString getExplain() const;

	/**
	 * オプションパラメータ追加
	 *
	 * @param const TString &szName				オプションパラメータ名
	 * @param const TString &szExplain			詳細
	 */
	void addOption(const TString &szName, const TString &szExplain);

	/**
	 * オプションパラメータ一覧の取得
	 *
	 * @param std::list<TString> &optionList	取得された一覧
	 * @return	int
	 */
	int getOptionList(std::list<TString> &optionList);

	/**
	 * オプションパラメータの詳細取得
	 *
	 * @param const TString &optionName			オプションパラメータ名
	 * @return	TString							詳細
	 */
	TString getOptionExplain(const TString &optionName);

	/**
	 * オプションパラメータの有無を取得
	 *
	 * @return	bool		true	: あり
	 *						false	: なし
	 */
	bool hasOptionParams() const;

private:
	TString							ml_szAppName;
	TString							ml_szExplain;
	ATAppOptionMap					ml_oOptionMap;
};
#endif // __ATUTLAPPINFO_H__DA2E17D2_3CFD_410F_812D_4D717ECCE339