
// ATutlBatchManagerDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "profile/ATutlAppInfo.h"
#include "execute/ATutlExecuteThread.h"
/**
 * CATutlBatchManagerDlg ダイアログ
 *
 * @autho jf-orange
 */
class CATutlBatchManagerDlg : public CDialogEx
{
public:
	/**
	 * コンストラクタ
	 */
	CATutlBatchManagerDlg(CWnd* pParent = NULL);

	/**
	 * デストラクタ
	 */
	virtual ~CATutlBatchManagerDlg();

	// ダイアログ データ
	enum { IDD = IDD_ATUTLBATCHMANAGER_DIALOG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;

private:

	/**
	 * 初期化処理
	 *
	 * @return		int
	 */
	int initialize();

	/**
	 * リストコントロールの初期化処理
	 *
	 * @return		int
	 */
	int initListCtrl();

	/**
	 * バッチアプリケーション情報の更新
	 *
	 * @param		const TString &szAppName	アプリ名
	 */
	void updateAppInfo(const TString &szAppName);

	/**
	 * 実行時チェック
	 *
	 * @return		true	: 実行可
	 *				false	: 実行不可
	 */
	bool validate();

	/**
	 * 実行時のコマンドライン作成
	 *
	 * @return		コマンドライン文字列
	 */
	TString createCmdLine();


	CEdit					ml_oStdoutEdit;			/* 標準出力用CEdit							*/
	CEdit					ml_oExplainEdit;		/* アプリケーション詳細CEdit				*/
	CEdit					ml_oOutputFolderEdit;	/* 出力用フォルダCEdit						*/
	ATListCtrl				ml_oOptParamListCtrl;
	CComboBox				ml_oApplicationCombo;
	std::list<ATAppInfo>	ml_oAppInfoList;

	HANDLE					ml_hStdOut;				// 標準出力ハンドル
	HANDLE					ml_hReadStdOut;			// 標準出力読み込みハンドル

	TString					ml_szOutputDir;			// 出力ディレクトリ
	TString					ml_szLogDir;			// ログディレクトリ
	TString					ml_szBaseDir;			// 基準ディレクトリ
	ATExecuteThread			*ml_pExecuteThread;		// 実行スレッド
	ATAppInfo				ml_oExecuteAppInfo;		// 実行アプリケーション
public:
	afx_msg void OnBnClickedButtonFinish();
	afx_msg void OnCbnSelchangeComboModule();	
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonRef();
	
	afx_msg void OnBnClickedButtonHalt();
};
