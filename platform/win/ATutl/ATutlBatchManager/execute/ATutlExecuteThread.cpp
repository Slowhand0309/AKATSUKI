#include "stdafx.h"
#include "ATutlExecuteThread.h"
#include "ATlib/utl/ATlibStringUtl.h"

//********************************************************************************************
/**
 * @brief		�R���X�g���N�^
 *              
 * @param[in]	�Ȃ�.
 */
//********************************************************************************************
ATExecuteThread::ATExecuteThread()
	: ml_pEdit(NULL)
{
}

//********************************************************************************************
/**
 * @brief		�f�X�g���N�^
 *              
 * @param[in]	�Ȃ�.
 */
//********************************************************************************************
ATExecuteThread::~ATExecuteThread()
{
}

//********************************************************************************************
/**
 * @brief		���s�p�X�̐ݒ�
 *              
 * @param[in]	const TString &szCmdLine		���s�p�X.
 */
//********************************************************************************************
void ATExecuteThread::setCmdLine(const TString &szCmdLine)
{
	ml_szCmdLine = szCmdLine;
}

//********************************************************************************************
/**
 * @brief		�ʒm��CEdit�̐ݒ�
 *              
 * @param[in]	CEdit *pEdit					�ʒm��.
 */
//********************************************************************************************
void ATExecuteThread::setNotifyEdit(CEdit *pEdit)
{
	ml_pEdit = pEdit;
}

//********************************************************************************************
/**
 * @brief		�X���b�h���̏���������
 *              
 * @param[in]	�Ȃ�.
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
 * @brief		�X���b�h���̏I������
 *              
 * @param[in]	�Ȃ�.
 *
 * @return		�Ȃ�
 */
//********************************************************************************************
void ATExecuteThread::finalize()
{
}

//********************************************************************************************
/**
 * @brief		�X���b�h���̎��s����
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

	/* �O���A�v���P�[�V���������s		*/
	int nRet = execute();
	if (nRet != AT_OK) {
		return nRet;
	}

	/* �A�v���P�[�V�������I������܂ő҂�	*/
	stopProccess();

	/* ���s���ʒʒm						*/
	notifyExecuteResult();

	CloseHandle(ml_hReadStdOut);
	CloseHandle(ml_hStdOut);

	return AT_OK;
}

//********************************************************************************************
/**
 * @brief		���s���ʒʒm
 *              
 * @param[in]	�Ȃ�.
 *
 * @return		�Ȃ�
 */
//********************************************************************************************
void ATExecuteThread::notifyExecuteResult()
{
	/* �W���o�͂̃��_�C���N�g���ꂽ�������擾		*/
	TString szMsg = _T("#################################################################################\r\n");
	szMsg += _T("# execute : ") + ml_szCmdLine + _T("\r\n");
	szMsg += _T("#################################################################################\r\n");

	char szStdOut[1024];
	DWORD dwReadByte;

	ZeroMemory(szStdOut, sizeof(szStdOut));

	BOOL bRet = ReadFile(ml_hReadStdOut, szStdOut, sizeof(szStdOut), &dwReadByte, NULL);
	if (!bRet) {
		szMsg += _T("�ʃv���Z�X�̕W���o�͂̎擾�Ɏ��s���܂����B\r\n");
	} else {
		szMsg += CString(szStdOut);
	}
	szMsg += _T("\r\n");
	
	notifyWindow(szMsg);
}

//********************************************************************************************
/**
 * @brief		�X���b�h���̎��s����
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

	/* �p�C�v�̍쐬		*/
	HANDLE hTemp = NULL;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	CreatePipe(&hTemp, &ml_hStdOut, &sa, 0);

	/* �n���h���̕���	*/
	DuplicateHandle(
		GetCurrentProcess(), 
		hTemp, 
		GetCurrentProcess(), 
		&ml_hReadStdOut, 
		0, 
		TRUE, 
		DUPLICATE_SAME_ACCESS);

	CloseHandle(hTemp);

	/* �ʃv���Z�X�̕W���o�͂����_�C���N�g	*/
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
 * @brief		�X���b�h���̎��s����
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
 * @brief		�ʃv���Z�X�̏I��
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
 * @brief		�ʃv���Z�X�̋����I��
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