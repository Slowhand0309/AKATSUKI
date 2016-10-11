/**
 * ファイルブラウザクラス実装<br>
 * <b>ATutlFileBrowser.cpp</b>
 *
 * @author slowhand0309
 */
#include "stdafx.h"
#include "ATlib/utl/ATlibDateUtl.h"
#include "ATutlFileBrowser.h"

#define BROWSE_FOLDER_TITLE				_T("フォルダの選択")
#define	FILE_TIME_FORMAT				_T("%d/%d/%d %d:%d:%d")

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATFileBrowser::ATFileBrowser()
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
ATFileBrowser::~ATFileBrowser()
{
}

//********************************************************************************************
/**
 * フォルダー参照
 *
 * @param			なし.
 * @return			参照パス
 *					エラー時やキャンセル時は空文字
 */
//********************************************************************************************
TString ATFileBrowser::browseFolder()
{
	BROWSEINFO			stBrowseInfo;
	LPITEMIDLIST		pIdList;
	TCHAR				szPath[_MAX_PATH] = {0};

	/* フォルダ選択ダイアログの設定		*/
	stBrowseInfo.hwndOwner             = AfxGetMainWnd()->m_hWnd;	// 親ウインドウのハンドル
	stBrowseInfo.pidlRoot              = NULL;						// デフォルトパス（NULL：デスクトップ）
	stBrowseInfo.pszDisplayName        = szPath;					// 選択されたパス受け取り用バッファ
	stBrowseInfo.lpszTitle             = BROWSE_FOLDER_TITLE;		// ダイアログに表示するタイトル 
	stBrowseInfo.ulFlags               = BIF_RETURNONLYFSDIRS;
	stBrowseInfo.lpfn                  = NULL;
	stBrowseInfo.lParam                = (LPARAM)0;

	//フォルダ選択ダイアログ　表示
	pIdList = ::SHBrowseForFolder(&stBrowseInfo);
	if(pIdList == NULL){
		/*	キャンセル時		*/
		return AT_EMPTY_STR;
	} else {
		/*	選択された場合		*/
		if(!::SHGetPathFromIDList(pIdList, szPath)){
			/*	エラー時		*/
			return AT_EMPTY_STR;
		}

		/* pIdListのポイントしているメモリを開放	*/
		::CoTaskMemFree(pIdList);
	}

	return TString(szPath);
}

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
int ATFileBrowser::getFileList(const TString &szDir, 
		const TString &szExt, std::list<FileProperty> &oFileList)
{
	HANDLE				hSearch;
	WIN32_FIND_DATA		fd;
	TString				szFileName = szDir + _T("\\*.") + szExt;

	hSearch = FindFirstFile(szFileName.c_str(), &fd);
	if(hSearch == INVALID_HANDLE_VALUE){
		return AT_ERR_HANDLE;
	}

	/* ファイル数分ループ		*/
	while (1) {
		FileProperty	oProperty;

		/* ファイル名を取得		*/
		TString szBuff(fd.cFileName);
		if (ATStringUtl::isEmpty(szBuff)) {
			continue;
		}

		/* ファイル名称が「.」か「..」の場合はスキップ	*/
		if (ATStringUtl::contains(szBuff, _T(".")) 
			|| ATStringUtl::contains(szBuff, _T(".."))) {
				continue;
		}

		/* 属性、作成日時、更新日時を取得	*/
		TString szAttribute = getFileArrtibuteStr(fd.dwFileAttributes);
		TString szCreateDate = getFileTimeStr(fd.ftCreationTime);
		TString szUpdateDate = getFileTimeStr(fd.ftLastWriteTime);

		oProperty.m_szFileName = szBuff;
		oProperty.m_szAttribute = szAttribute;
		oProperty.m_szCreateDate = szCreateDate;
		oProperty.m_szUpdateDate = szUpdateDate;

		oFileList.push_back(oProperty);

		// 次のファイルへ進む
		if(!FindNextFile(hSearch, &fd)){
			if(GetLastError() == ERROR_NO_MORE_FILES){
				break;
			} else {
				FindClose( hSearch );
				return AT_ERR_HANDLE;
			}
		}
	}

	FindClose(hSearch);
	return AT_OK;
}

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
TString ATFileBrowser::getFileArrtibuteStr(const DWORD dwAttribute)
{
	TString szValue = _T("");

	if(dwAttribute & FILE_ATTRIBUTE_DIRECTORY){
		szValue = _T("ディレクトリ");
	} else if(dwAttribute & FILE_ATTRIBUTE_ARCHIVE){
		szValue = _T("アーカイブ");
	} else if(dwAttribute & FILE_ATTRIBUTE_COMPRESSED){
		szValue = _T("圧縮ファイル");
	} else if(dwAttribute & FILE_ATTRIBUTE_HIDDEN){
		szValue = _T("隠しファイル");
	} else if(dwAttribute & FILE_ATTRIBUTE_NORMAL){
		szValue = _T("ファイル");
	} else if(dwAttribute & FILE_ATTRIBUTE_READONLY){
		szValue = _T("読取専用");
	} else if(dwAttribute & FILE_ATTRIBUTE_SYSTEM){
		szValue = _T("システムファイル");
	} else if(dwAttribute & FILE_ATTRIBUTE_TEMPORARY){
		szValue = _T("一時ファイル");
	} else {
		szValue = _T("その他");
	}
	return szValue;
}

//********************************************************************************************
/**
 * ファイル属性の日時を文字列に変換する
 *
 * @param			日時文字列.
 *
 */
//********************************************************************************************
TString ATFileBrowser::getFileTimeStr(const FILETIME stFileTime)
{
	SYSTEMTIME stSystemTime;
	/* システム時間に変換	*/
	if(FileTimeToSystemTime(&stFileTime, &stSystemTime) == FALSE){
		return AT_EMPTY_STR;
	}

	/* フォーマット文字列として返却		*/
	return ATDateUtl::getFormatString(stSystemTime, FILE_TIME_FORMAT);
}