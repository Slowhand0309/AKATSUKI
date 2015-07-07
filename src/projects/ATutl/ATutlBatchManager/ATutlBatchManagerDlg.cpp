
// ATutlBatchManagerDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ATutlBatchManager.h"
#include "ATutlBatchManagerDlg.h"
#include "afxdialogex.h"

#include "ATlib/utl/ATlibStringUtl.h"
#include "ATutl/ATutlCommon/ATutlFileBrowser.h"
#include "profile/ATutlBatchManagerProfile.h"
#include "ATlib/utl/ATlibSysUtl.h"
#include "ATlib/utl/ATlibDateUtl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* INIファイル名称					*/
#define	INIFILE_PATH				_T("test.ini")

/* ----- ini file define ----- */
#define	KEY_APPLICATION				_T("APPLICATION")
#define KEY_BASE_DIR				_T("BASE_DIR")
#define KEY_OUT_DIR					_T("OUT_DIR")
#define KEY_LOG_DIR					_T("LOG_DIR")

/* ----- ctrl list define ----- */
#define LISTCTRL_HEADER_OPTION		_T("オプション")
#define LISTCTRL_HEADER_EXPLAIN		_T("説明")

#define EXECUTE_DATETIME_FMT		_T("%Y%m%d_%H%M%S")

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CATutlBatchManagerDlg ダイアログ




CATutlBatchManagerDlg::CATutlBatchManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CATutlBatchManagerDlg::IDD, pParent)
	, ml_pExecuteThread(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CATutlBatchManagerDlg::~CATutlBatchManagerDlg()
{
	AT_SAFE_DELETE(ml_pExecuteThread);
}

void CATutlBatchManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODULE, ml_oApplicationCombo);
	DDX_Control(pDX, IDC_LIST_OPT_PARAM, ml_oOptParamListCtrl);
	DDX_Control(pDX, IDC_EDIT_EXPLAIN, ml_oExplainEdit);
	DDX_Control(pDX, IDC_EDIT_OUTDIR, ml_oOutputFolderEdit);
	DDX_Control(pDX, IDC_EDIT_STDOUT, ml_oStdoutEdit);
}

BEGIN_MESSAGE_MAP(CATutlBatchManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_FINISH, &CATutlBatchManagerDlg::OnBnClickedButtonFinish)
	ON_CBN_SELCHANGE(IDC_COMBO_MODULE, &CATutlBatchManagerDlg::OnCbnSelchangeComboModule)
	ON_BN_CLICKED(ID_BUTTON_RUN, &CATutlBatchManagerDlg::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_REF, &CATutlBatchManagerDlg::OnBnClickedButtonRef)
	ON_BN_CLICKED(IDC_BUTTON_HALT, &CATutlBatchManagerDlg::OnBnClickedButtonHalt)
END_MESSAGE_MAP()


// CATutlBatchManagerDlg メッセージ ハンドラー

BOOL CATutlBatchManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	/* 初期化処理							*/
	if (initialize() != AT_OK) {
		/* 初期化失敗の場合はアプリ終了		*/
		CDialogEx::OnCancel();
	}

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

//********************************************************************************************
/**
 * 初期化処理
 *
 * @return	int
 */
//********************************************************************************************
int CATutlBatchManagerDlg::initialize() 
{
	/* INIファイル読み込み		*/
	ATBatchManagerProfile profile;
	int nRet = profile.readProfile(INIFILE_PATH);
	if (nRet != AT_OK) {
		ATMessageBoxError(_T("INIファイルの読み込みに失敗しました"));
		return nRet;
	}

	/* アプリケーションリスト取得	*/
	ml_oAppInfoList = profile.getAppInfoList();
	if (ml_oAppInfoList.size() == 0) {
		ATMessageBoxError(_T("アプリケーション一覧の読み込みに失敗しました"));
		return AT_ERR_NOTFOUND;
	}

	/* モジュールコンボボックスへ設定	*/
	std::list<ATAppInfo>::iterator it;
	for (it = ml_oAppInfoList.begin(); it != ml_oAppInfoList.end(); ++it) {
		ml_oApplicationCombo.AddString(T2CString(it->getName()));
	}

	/* 基準ディレクトリの取得			*/
	ml_szBaseDir = profile.getBaseDir();
	if (ATStringUtl::isEmpty(ml_szBaseDir)) {
		ATMessageBoxError(_T("設定ファイルに基準ディレクトリが設定されていません"));
		return AT_ERR_SETTINGS;
	}

	/* ログディレクトリの取得			*/
	ml_szLogDir = profile.getLogDir();

	/* 出力ディレクトリの設定			*/
	ml_szOutputDir = profile.getOutputDir();
	if (ATStringUtl::isEmpty(ml_szOutputDir)) {
		ATMessageBoxError(_T("設定ファイルに出力ディレクトリが設定されていません"));
		return AT_ERR_SETTINGS;
	}
	ml_oOutputFolderEdit.SetWindowText(ml_szOutputDir.c_str());

	nRet = initListCtrl();
	return nRet;
}

//********************************************************************************************
/**
 * リストコントロール初期化処理
 *
 * @return	int
 */
//********************************************************************************************
int CATutlBatchManagerDlg::initListCtrl()
{
	/* オプションパラメータリスト初期化		*/
	ml_oOptParamListCtrl.setGridLineStyle();
	ml_oOptParamListCtrl.setCheckBoxStyle();
	
	ml_oOptParamListCtrl.insertHeadItem(0, CString(LISTCTRL_HEADER_OPTION), 60);
	ml_oOptParamListCtrl.insertHeadItem(1, CString(LISTCTRL_HEADER_EXPLAIN), 200);

	return AT_OK;
}

//********************************************************************************************
/**
 * リストコントロール初期化処理
 *
 * @return	int
 */
//********************************************************************************************
void CATutlBatchManagerDlg::updateAppInfo(const TString &szAppName)
{
	if (ATStringUtl::isEmpty(szAppName)) {
		return;
	}

	/* 各コントロール初期化		*/
	ml_oOptParamListCtrl.DeleteAllItems();
	ml_oExplainEdit.SetWindowText(AT_EMPTY_STR);

	std::list<ATAppInfo>::iterator it;
	for (it = ml_oAppInfoList.begin(); it != ml_oAppInfoList.end(); ++it) {
		if (szAppName == it->getName()) {
			/* 詳細の更新									*/
			ml_oExplainEdit.SetWindowText(T2CString(it->getExplain()));

			/* 対象アプリケーションのオプション一覧を更新	*/
			if (!it->hasOptionParams()) {
				continue;
			}
			std::list<TString> optionList;
			if (it->getOptionList(optionList) == AT_OK) {
				/* オプション一覧をリストへ設定		*/
				int index = 0;
				std::list<TString>::iterator iit;
				for (iit = optionList.begin(); iit != optionList.end(); ++iit, index++) {
					ml_oOptParamListCtrl.setListData(index, 0, T2CString((*iit)));
					/* オプションの説明		*/
					TString szExplain = it->getOptionExplain((*iit));
					if (ATStringUtl::isNotEmpty(szExplain)) {
						ml_oOptParamListCtrl.setListData(index, 1, T2CString(szExplain));
					}
				}
			}
		}
	}
}

void CATutlBatchManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CATutlBatchManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CATutlBatchManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//********************************************************************************************
/**
 * 実行時チェック処理
 *
 * @return	bool		true	: 実行可
 *						false	: 実行不可
 */
//********************************************************************************************
bool CATutlBatchManagerDlg::validate()
{
	int nIdx = ml_oApplicationCombo.GetCurSel();
	if (nIdx < 0) {
		/* アプリ未選択			*/
		ATMessageBoxWarning(_T("実行アプリケーションが選択されていません"));
		return false;
	}

	int nCount = 0;
	std::list<ATAppInfo>::iterator it;
	for (it = ml_oAppInfoList.begin(); it != ml_oAppInfoList.end(); it++, nCount++) {
		if (nIdx == nCount) {
			break;
		}
	}

	if (it->hasOptionParams()) {
		/* 必須オプションチェック	*/
	}

	/* 実行アプリケーション存在チェック		*/
	TString szCmdLine = ml_szBaseDir + _T("\\") + it->getName();
	if (!ATSysUtl::hasPath(szCmdLine)) {
		TString msg = _T("実行アプリケーションのパスが不正です\n「") + szCmdLine + _T("」");
		ATMessageBoxWarning(msg.c_str());
		return false;
	}

	ml_oExecuteAppInfo = *it;
	return true;
}

//********************************************************************************************
/**
 * アプリケーション選択時
 *
 * @return	なし
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnCbnSelchangeComboModule()
{
	/* 現在の設定値を取得	*/
	CString szAppName;
	ml_oApplicationCombo.GetLBText(ml_oApplicationCombo.GetCurSel(), szAppName);

	/* 詳細とオプション一覧を更新			*/
	updateAppInfo(C2TString(szAppName));
}

//********************************************************************************************
/**
 * 「終了」ボタン押下時
 *
 * @return	なし
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnBnClickedButtonFinish()
{
	CDialogEx::OnCancel();
}

//********************************************************************************************
/**
 * 「実行」ボタン押下時
 *
 * @return	なし
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnBnClickedButtonRun()
{
	int nRet = ATMessageBoxQuestion(_T("アプリケーションを実行してもよろしいですか？"));
	if (nRet == IDNO) {
		/* 実行キャンセル		*/
		return;
	}

	if (!validate()) {
		/* 実行時チェックNG		*/
		return;
	}

	TRACE(_T("execute app name : %ls \n"), ml_oExecuteAppInfo.getName().c_str());
	TRACE(_T("execute app explain : %ls \n"), ml_oExecuteAppInfo.getExplain().c_str());

	AT_SAFE_DELETE(ml_pExecuteThread);

	/* コマンドライン作成	*/
	TString szCmdLine = createCmdLine();

	ml_pExecuteThread = new ATExecuteThread();
	ml_pExecuteThread->setCmdLine(szCmdLine);
	ml_pExecuteThread->setNotifyEdit(&ml_oStdoutEdit);

	ml_pExecuteThread->startThread(0);
}

//********************************************************************************************
/**
 * コマンドライン文字列の作成
 *
 * @return	コマンドライン文字列
 */
//********************************************************************************************
TString CATutlBatchManagerDlg::createCmdLine()
{
	CString szBuff;

	/* コマンドライン作成	*/
	TString szCmdLine = ml_szBaseDir + _T("\\") + ml_oExecuteAppInfo.getName();

	// 1: 実行時間
	TString szDate = ATDateUtl::getCurrentDate(EXECUTE_DATETIME_FMT);

	// 2: ログ出力先

	// 3: 出力先
	ml_oOutputFolderEdit.GetWindowText(szBuff);
	ml_szOutputDir = szBuff;

	szCmdLine += _T(" \"") + szDate + _T("\" \"") + ml_szLogDir + _T("\" \"") + ml_szOutputDir + _T("\"");

	/* オプションパラメータの設定		*/
	std::list<CString> oCheckList;
	ml_oOptParamListCtrl.getCheckColumnData(oCheckList);

	std::list<CString>::iterator it;
	for (it = oCheckList.begin(); it != oCheckList.end(); ++it) {
		szCmdLine += _T(" ") + *it;
	}

	TRACE(_T("execute app cmdline : %ls \n"), szCmdLine.c_str());

	return szCmdLine;
}

//********************************************************************************************
/**
 * 出力先「参照」ボタン押下時
 *
 * @return	なし
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnBnClickedButtonRef()
{
	ATFileBrowser oBrowser;
	TString path = oBrowser.browseFolder();

	if (ATStringUtl::isNotEmpty(path)) {
		ml_oOutputFolderEdit.SetWindowText(path.c_str());
	}
}

//********************************************************************************************
/**
 * 「バッチ強制終了」ボタン押下時
 *
 * @return	なし
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnBnClickedButtonHalt()
{
	if (ml_pExecuteThread != NULL) {
		ml_pExecuteThread->haltProcess();
	}
}