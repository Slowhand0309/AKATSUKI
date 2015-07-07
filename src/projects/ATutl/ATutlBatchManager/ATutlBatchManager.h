
// ATutlBatchManager.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CATutlBatchManagerApp:
// このクラスの実装については、ATutlBatchManager.cpp を参照してください。
//

class CATutlBatchManagerApp : public CWinApp
{
public:
	CATutlBatchManagerApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CATutlBatchManagerApp theApp;