/**
 * �X���b�h���N���X����<br>
 * <b>ATutlBaseThread.cpp</b>
 *
 * @author slowhand0309
 */
#include "stdafx.h"
#include "ATutlBaseThread.h"

//********************************************************************************************
/**
 * @brief		�R���X�g���N�^
 *              
 * @param[in]	�Ȃ�.
 */
//********************************************************************************************
ATBaseThread::ATBaseThread()
	: ml_pThread(NULL)
{
}

//********************************************************************************************
/**
 * @brief		�f�X�g���N�^
 *              
 * @param[in]	�Ȃ�.
 */
//********************************************************************************************
ATBaseThread::~ATBaseThread()
{
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
int ATBaseThread::initialize()
{
	/* �K�v�ɉ����Čp����Ŏ���			*/
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
void ATBaseThread::finalize()
{
	/* �K�v�ɉ����Čp����Ŏ���			*/
}

//********************************************************************************************
/**
 * @brief		�X���b�h�J�n
 *
 * @param[in]	int nPriority			�D��x
 *
 * @return		int						AT_OK ����I�� : AT_ERR_HANDLE �ُ�I��
 */
//********************************************************************************************
int ATBaseThread::startThread(int	nPriority)
{
	ml_pThread = AfxBeginThread( 	ATBaseThread::l_ThreadFunc,
									this,
									nPriority,
									0,
									CREATE_SUSPENDED,	/* CWinThread::ResumeThread���Ăяo���Ă���X���b�h���s  */
									NULL );
	if (ml_pThread == NULL)
	{
		return AT_ERR_HANDLE;
	}

	/* �I�u�W�F�N�g�̎����폜 : ON */
	ml_pThread->m_bAutoDelete = TRUE;
	/* �X���b�h�ĊJ */
	ml_pThread->ResumeThread();

	return AT_OK;
}

//********************************************************************************************
/**
 * @brief		�X���b�h����֐���`
 *
 * @param[in]	LPVOID pParam			ATBaseThread
 *
 * @return		int						0 ����I�� : -1 �ُ�I��
 */
//********************************************************************************************
UINT ATBaseThread::l_ThreadFunc(LPVOID pParam)
{
	UINT nRet;

	ATBaseThread *pSelf = (ATBaseThread *)pParam;
	nRet = pSelf->initialize();
	nRet = pSelf->run(pParam);
	pSelf->finalize();

	return nRet;
}