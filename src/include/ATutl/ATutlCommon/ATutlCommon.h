// ATutlCommon.h : ATutlCommon.DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

/* ----- header include ----- */
#include "resource.h"		// メイン シンボル
#include "ATutl/ATutlCommon/ATutlListCtrl.h"
#include "ATutl/ATutlCommon/ATutlProfile.h"
#include "ATutl/ATutlCommon/ATutlFileBrowser.h"
#include "ATutl/ATutlCommon/ATutlBaseThread.h"

/* ----- define  ----- */
#define ERROR_MSG_TITLE					_T("エラー")
#define WARNING_MSG_TITLE				_T("警告")
#define INFO_MSG_TITLE					_T("情報")
#define QEUSTION_MSG_TITLE				_T("確認")

/* ----- define utilitys ----- */
#define ATMessageBoxError(msg)			MessageBox(msg, ERROR_MSG_TITLE, MB_OK | MB_ICONERROR)
#define ATMessageBoxWarning(msg)		MessageBox(msg, WARNING_MSG_TITLE, MB_OK | MB_ICONEXCLAMATION)
#define ATMessageBoxInfo(msg)			MessageBox(msg, INFO_MSG_TITLE, MB_OK | MB_ICONINFORMATION)
#define ATMessageBoxQuestion(msg)		MessageBox(msg, QEUSTION_MSG_TITLE, MB_YESNO | MB_ICONINFORMATION)

/* TStringからCStringへ変換する		*/
#define T2CString(t)					CString(t.c_str())
/* CStringからTStringへ変換する		*/
#define	C2TString(c)					TString(c)

// CATutlCommonApp
// このクラスの実装に関しては ATutlCommon.cpp を参照してください。
//

class CATutlCommonApp : public CWinApp
{
public:
	CATutlCommonApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
