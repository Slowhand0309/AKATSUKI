#ifndef __ATUTLPROFILE_H__19DCC682_5461_4291_8D3E_DBA249A2457B
#define __ATUTLPROFILE_H__19DCC682_5461_4291_8D3E_DBA249A2457B
#include "ATlib/com/ATlibCommon.h"

typedef std::map<TString, std::list<TString>> ATProfileData;

/**
 * INIファイル処理クラス<br>
 * <b>ATutlProfile.h</b>
 *
 * @author slowhand0309
 */
class ATProfile
{
public:
	/**
	 * コンストラクタ
	 */
	ATProfile();

	/**
	 * コンストラクタ
	 *
	 * @param const TString &szFileName		iniファイルパス
	 */
	ATProfile(const TString &szFileName);

	/**
	 * デストラクタ
	 */
	virtual ~ATProfile();
	
	/**
	 * データ初期化
	 */
	void clear();

	/**
	 * iniファイル読み込み
	 *
	 * @param const TString &szFileName		iniファイルパス
	 */
	virtual int readProfile(const TString &szFileName);

	/**
	 * データ取得
	 *
	 * @param const TString &szKey				キー
	 * @param std::list<TString> &listValues	データリスト
	 */
	int getValues(const TString &szKey, std::list<TString> &listValues);

protected:
	TString				ml_szFileName;
	ATProfileData		ml_mapList;
};
#endif // __ATUTLPROFILE_H__19DCC682_5461_4291_8D3E_DBA249A2457B