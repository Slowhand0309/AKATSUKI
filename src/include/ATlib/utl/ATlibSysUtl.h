#ifndef __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B
#define __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B

#include "ATlib/com/ATlibCommon.h"

class ATSysUtl
{
public:

	/**
	 * モジュール名の取得
	 *
	 * @return	TString		モジュール名
	 */
	static TString getModuleName() {

		TString		strRet = _T("");
		TCHAR	szFullPath[_MAX_PATH] = {0};
		TCHAR	szFname[_MAX_FNAME] = {0};

#ifdef PLATFORM_WINDOWS
		// 現在のモジュール名を含めた完全フルパスを取得
		GetModuleFileName(GetModuleHandle(NULL), szFullPath, _MAX_PATH);

		// パス, モジュール名, 拡張子, それぞれに分解する
		_tsplitpath_s(szFullPath, NULL, 0, NULL, 0, szFname, _MAX_FNAME, NULL, 0);
#else
#endif // PLATFORM_WINDOWS

		strRet = TString(szFname);
		return strRet;
	};

	/**
	 * 現在の実行モジュールのパスを取得
	 *
	 * @return TString			パス
	 */
	static TString getCurrentPath() {

		TCHAR	szFullPath[_MAX_PATH] = {0};
		TCHAR	szDir[_MAX_DIR] = {0};
		TCHAR	szFname[_MAX_FNAME] = {0};
		TCHAR	szExt[_MAX_EXT] = {0};

#ifdef PLATFORM_WINDOWS
		// 現在のモジュール名を含めた完全フルパスを取得
		GetModuleFileName(GetModuleHandle(NULL), szFullPath, _MAX_PATH);

		// パス, モジュール名, 拡張子, それぞれに分解する
		_tsplitpath_s( szFullPath, NULL, 0, szDir, _MAX_DIR
			, szFname, _MAX_FNAME, szExt, _MAX_EXT );

#else
#endif // PLATFORM_WINDOWS
		return TString(szDir);
	};

	/**
	 * パス文字列から拡張子を取得<br>
	 * 拡張子が存在しない場合空文字を返す
	 * 
	 * @param const TString &szPath		パス文字列
	 * @return TString					拡張子
	 */
	static TString getExtension(const TString &szPath) {

		TString		szExtension = _T("");
		unsigned int uiPoint = 0;

		if(szPath.empty()){
			return _T(""); 
		}

		unsigned int uiStrLen = szPath.length();
		while(szPath[uiPoint] != _T('\0')){

			/* 拡張子が見つかった時点でループを抜ける	*/
			if(szPath[uiPoint] == _T('.')){
				break;
			}
			++uiPoint;
			
			if(static_cast<unsigned int>(szPath.length()) <= uiPoint){
				/* 最後まで拡張子が見つからなかった場合		*/
				return _T("");
			}
		}

		szExtension = szPath.substr(++uiPoint);
		return szExtension;
	};

	/**
	 * パスの有効性チェック
	 *
	 * @param const TString &szPath		パス
	 * @return		true	: 有効
	 *				false	: 無効
	 */
	static bool hasPath(const TString &szPath) {

		int		iRet = 0;
		struct _stat tagStat;

		if(szPath.empty()){
			return false;
		}
	
		/* 指定されたファイルパスの情報を取得	*/
		iRet = _tstat(szPath.c_str(), &tagStat);
		if(iRet != 0){
			if(errno == ENOENT){
				/* ファイルが存在しない		*/
			} else if(errno == EINVAL){
				/* _tstat エラー			*/
			}
			return false;
		}
		return true;
	}

private:
	ATSysUtl();
};
#endif // __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B