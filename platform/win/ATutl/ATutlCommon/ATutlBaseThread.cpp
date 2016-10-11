/**
 * スレッド基底クラス実装<br>
 * <b>ATutlBaseThread.cpp</b>
 *
 * @author slowhand0309
 */
#include "stdafx.h"
#include "ATutlBaseThread.h"

//********************************************************************************************
/**
 * @brief		コンストラクタ
 *              
 * @param[in]	なし.
 */
//********************************************************************************************
ATBaseThread::ATBaseThread()
	: ml_pThread(NULL)
{
}

//********************************************************************************************
/**
 * @brief		デストラクタ
 *              
 * @param[in]	なし.
 */
//********************************************************************************************
ATBaseThread::~ATBaseThread()
{
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
int ATBaseThread::initialize()
{
	/* 必要に応じて継承先で実装			*/
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
void ATBaseThread::finalize()
{
	/* 必要に応じて継承先で実装			*/
}

//********************************************************************************************
/**
 * @brief		スレッド開始
 *
 * @param[in]	int nPriority			優先度
 *
 * @return		int						AT_OK 正常終了 : AT_ERR_HANDLE 異常終了
 */
//********************************************************************************************
int ATBaseThread::startThread(int	nPriority)
{
	ml_pThread = AfxBeginThread( 	ATBaseThread::l_ThreadFunc,
									this,
									nPriority,
									0,
									CREATE_SUSPENDED,	/* CWinThread::ResumeThreadを呼び出してからスレッド実行  */
									NULL );
	if (ml_pThread == NULL)
	{
		return AT_ERR_HANDLE;
	}

	/* オブジェクトの自動削除 : ON */
	ml_pThread->m_bAutoDelete = TRUE;
	/* スレッド再開 */
	ml_pThread->ResumeThread();

	return AT_OK;
}

//********************************************************************************************
/**
 * @brief		スレッド制御関数定義
 *
 * @param[in]	LPVOID pParam			ATBaseThread
 *
 * @return		int						0 正常終了 : -1 異常終了
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