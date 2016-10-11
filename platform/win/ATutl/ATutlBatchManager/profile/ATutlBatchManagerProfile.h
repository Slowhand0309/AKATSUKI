#ifndef __ATUTLBATCHMANAGERPROFILE_H__D3C7D203_F8CF_44C1_BF07_D8AAABA6CA6E
#define __ATUTLBATCHMANAGERPROFILE_H__D3C7D203_F8CF_44C1_BF07_D8AAABA6CA6E

#include "ATutlAppInfo.h"

class ATBatchManagerProfile : public ATProfile
{
public:
	/**
	 * コンストラクタ
	 */
	ATBatchManagerProfile();

	/**
	 * コンストラクタ
	 * 
	 * @param const TString &szFileName		ファイル名
	 */
	ATBatchManagerProfile(const TString &szFileName);

	/**
	 * デストラクタ
	 */
	virtual ~ATBatchManagerProfile();

	/**
	 * iniファイル読み込み
	 *
	 * @param const TString &szFileName		iniファイルパス
	 */
	virtual int readProfile(const TString &szFileName);

	/**
	 * アプリケーション情報リスト取得
	 *
	 * @param	std::list<ATAppInfo> &oAppInfoList	アプリケーションリスト
	 * @return	int
	 */
	std::list<ATAppInfo> getAppInfoList();

	/**
	 * 基準ディレクトリの取得
	 *
	 * @return TString
	 */
	TString getBaseDir();

	/**
	 * ログディレクトリの取得
	 *
	 * @return TString
	 */
	TString getLogDir();

	/**
	 * 出力ディレクトリの取得
	 *
	 * @return	TString
	 */
	TString getOutputDir();

private:

	std::list<ATAppInfo>			ml_oAppInfoList;
};
#endif // __ATUTLBATCHMANAGERPROFILE_H__D3C7D203_F8CF_44C1_BF07_D8AAABA6CA6E