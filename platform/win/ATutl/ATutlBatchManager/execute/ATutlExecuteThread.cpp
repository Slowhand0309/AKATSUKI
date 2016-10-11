#include "stdafx.h"
#include "ATutlExecuteThread.h"
#include "ATlib/utl/ATlibStringUtl.h"

//********************************************************************************************
/**
 * @brief		コンストラクタ
 *              
 * @param[in]	なし.
 */
//********************************************************************************************
ATExecuteThread::ATExecuteThread()
	: ml_pEdit(NULL)
{
}

//********************************************************************************************
/**
 * @brief		デストラクタ
 *              
 * @param[in]	なし.
 */
//********************************************************************************************
ATExecuteThread::~ATExecuteThread()
{
}

//********************************************************************************************
/**
 * @brief		実行パスの設定
 *              
 * @param[in]	const TString &szCmdLine		実行パス.
 */
//********************************************************************************************
void ATExecuteThread::setCmdLine(const TString &szCmdLine)
{
	ml_szCmdLine = szCmdLine;
}

//********************************************************************************************
/**
 * @brief		通知先CEditの設定
 *              
 * @param[in]	CEdit *pEdit					通知先.
 */
//********************************************************************************************
void ATExecuteThread::setNotifyEdit(CEdit *pEdit)
{
	ml_pEdit = pEdit;
}

//********************************************************************************************
/**
 * @brief		スレッド内の初期化処理
 *              
 * @param[in]	なし.
 *
 * @return		int
 */
//********************************************************************************************
int ATExecuteThread::initialize()
{
	return AT_OK;
}

//********************************************************************************************
/**
 * @brief		スレッド内の終了処理
 *              
 * @param[in]	なし.
 *
 * @return		なし
 */
//********************************************************************************************
void ATExecuteThread::finalize()
{
}

//********************************************************************************************
/**
 * @brief		スレッド内の実行処理
 *              
 * @param[in]	LPVOID pParam				ATExecuteThread.
 *
 * @return		int
 */
//********************************************************************************************
int ATExecuteThread::run(LPVOID pParam)
{
	if (ATStringUtl::isEmpty(ml_szCmdLine)) {
		return AT_ERR_ARGUMENTS;
	}

	/* 外部アプリケーションを実行		*/
	int nRet = execute();
	if (nRet != AT_OK) {
		return nRet;
	}

	/* アプリケーションが終了するまで待つ	*/
	stopProccess();

	/* 実行結果通知						*/
	notifyExecuteResult();

	CloseHandle(ml_hReadStdOut);
	CloseHandle(ml_hStdOut);

	return AT_OK;
}

//********************************************************************************************
/**
 * @brief		実行結果通知
 *              
 * @param[in]	なし.
 *
 * @return		なし
 */
//********************************************************************************************
void ATExecuteThread::notifyExecuteResult()
{
	/* 標準出力のリダイレクトされた文字を取得		*/
	TString szMsg = _T("#################################################################################\r\n");
	szMsg += _T("# execute : ") + ml_szCmdLine + _T("\r\n");
	szMsg += _T("#################################################################################\r\n");

	char szStdOut[1024];
	DWORD dwReadByte;

	ZeroMemory(szStdOut, sizeof(szStdOut));

	BOOL bRet = ReadFile(ml_hReadStdOut, szStdOut, sizeof(szStdOut), &dwReadByte, NULL);
	if (!bRet) {
		szMsg += _T("別プロセスの標準出力の取得に失敗しました。\r\n");
	} else {
		szMsg += CString(szStdOut);
	}
	szMsg += _T("\r\n");
	
	notifyWindow(szMsg);
}

//********************************************************************************************
/**
 * @brief		スレッド内の実行処理
 *              
 * @param[in]	LPVOID pParam				ATExecuteThread.
 *
 * @return		int
 */
//********************************************************************************************
int ATExecuteThread::execute()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi = {};

	/* パイプの作成		*/
	HANDLE hTemp = NULL;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	CreatePipe(&hTemp, &ml_hStdOut, &sa, 0);

	/* ハンドルの複製	*/
	DuplicateHandle(
		GetCurrentProcess(), 
		hTemp, 
		GetCurrentProcess(), 
		&ml_hReadStdOut, 
		0, 
		TRUE, 
		DUPLICATE_SAME_ACCESS);

	CloseHandle(hTemp);

	/* 別プロセスの標準出力をリダイレクト	*/
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdOutput = ml_hStdOut;

	TCHAR	szPath[_MAX_PATH] = {0};
	_stprintf(szPath, _T("%ls"), ml_szCmdLine.c_str());

	::CreateProcess(NULL, szPath, NULL, NULL, 
		TRUE, NORMAL_PRIORITY_CLASS,
	    NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	ml_hProcHandle = pi.hProcess;

	return AT_OK;
}

//********************************************************************************************
/**
 * @brief		スレッド内の実行処理
 *              
 * @param[in]	LPVOID pParam				ATExecuteThread.
 *
 * @return		int
 */
//********************************************************************************************
void ATExecuteThread::notifyWindow(const TString &szMessage)
{
	if (ml_pEdit) {
		CString strBuff;
		ml_pEdit->GetWindowText(strBuff);
		strBuff += szMessage.c_str();
		ml_pEdit->SetWindowText(strBuff);
	}
}

//********************************************************************************************
/**
 * @brief		別プロセスの終了
 *              
 *
 * @param[in]	none.
 *
 * @return		none.
 */
//********************************************************************************************
void ATExecuteThread::stopProccess()
{
	if (ml_hProcHandle != NULL) {
		WaitForSingleObject(ml_hProcHandle, INFINITE);
		CloseHandle(ml_hProcHandle);
		ml_hProcHandle = NULL;
	}
}

//********************************************************************************************
/**
 * @brief		別プロセスの強制終了
 *              
 *
 * @param[in]	none.
 *
 * @return		none.
 */
//********************************************************************************************
void ATExecuteThread::haltProcess()
{
	if (ml_hProcHandle != NULL) {
		TerminateProcess(ml_hProcHandle, 0);
		ml_hProcHandle = NULL;
	}
}