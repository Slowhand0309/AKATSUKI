/**
 * INIファイル処理クラス実装<br>
 * <b>ATutlProfile.cpp</b>
 *
 * @author slowhand0309
 */
#include "stdafx.h"
#include "ATlib/utl/ATlibSysUtl.h"
#include "ATlib/utl/ATlibStringUtl.h"
#include "ATlib/io/ATlibFile.h"
#include "ATutl/ATutlCommon/ATutlProfile.h"

/* iniファイル内のコメント文字列		*/
#define COMMENT_MARK				_T(";")

/* iniファイル内キー項目識別文字		*/
#define KEY_MARK_START				_T("[")
#define KEY_MARK_END				_T("]")

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATProfile::ATProfile()
{
}

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			const TString &szFileName	iniファイルパス.
 *
 */
//********************************************************************************************
ATProfile::ATProfile(const TString &szFileName)
{
	this->readProfile(szFileName);
}

//********************************************************************************************
/**
 * デストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATProfile::~ATProfile()
{
}

//********************************************************************************************
/**
 * データ初期化
 *
 * @param			なし.
 *
 */
//********************************************************************************************
void ATProfile::clear()
{
	ml_mapList.clear();
}

//********************************************************************************************
/**
 * iniファイル読み込み
 *
 * @param	const TString &szFileName			iniファイルパス
 */
//********************************************************************************************
int ATProfile::readProfile(const TString &szFileName)
{
	int nRet;
	/* ファイルパスチェック		*/
	if (!ATSysUtl::hasPath(szFileName)) {
		return AT_ERR_ARGUMENTS;
	}

	clear();

	/* ファイルオープン			*/
	ATFile oFile;
	nRet = oFile.open(szFileName, OpenMode::OpenMode_TxtReadOnly);
	if (nRet != AT_OK) {
		return nRet;
	}

	TString szBuff;
	TString szKey;
	
	while (!oFile.isEof()) {
		szBuff.clear();

		/* 一行読み込み		*/
		nRet = oFile.read(szBuff);
		if (nRet == AT_OK) {
			if (ATStringUtl::isEmpty(szBuff) 
				|| szBuff.find(COMMENT_MARK, 0) == 0
				|| szBuff.find(_T("\n"), 0) == 0
				|| szBuff.find(_T("\r"), 0) == 0) {
				continue;
			}

			if (szBuff.find(KEY_MARK_START, 0) == 0) {
				/* キー項目	名称を取得	*/
				unsigned int location = szBuff.find(KEY_MARK_END, 1);
				szKey = szBuff.substr(1, location - 1);
				continue;
			}

			if (!szKey.empty()) {
				/* 末尾の改行コードを削除 */
				szBuff = szBuff.substr(0, szBuff.length() - 1);

				ATProfileData::iterator it = ml_mapList.find(szKey);
				if (it != ml_mapList.end()) {
					it->second.push_back(szBuff);
				} else {
					/* 新規のキー	*/
					std::list<TString> listValues;
					listValues.push_back(szBuff);
					ml_mapList.insert(std::make_pair<TString, std::list<TString>>(szKey, listValues));
				}
			}
		}
	}

	oFile.close();
	ml_szFileName = szFileName;
	return AT_OK;
}

//********************************************************************************************
/**
 * データ取得
 *
 * @param	const TString &szKey			キー
 * @param	std::list<TString> &listValues	データリスト
 * @return	int
 */
//********************************************************************************************
int ATProfile::getValues(const TString &szKey, std::list<TString> &listValues)
{
	if (ATStringUtl::isEmpty(szKey)) {
		return AT_ERR_ARGUMENTS;
	}

	/* iniファイル内のデータから検索	*/
	ATProfileData::iterator it = ml_mapList.find(szKey);
	if (it == ml_mapList.end()) {
		return AT_ERR_NOTFOUND;
	}
	listValues = it->second;
	return AT_OK;
}