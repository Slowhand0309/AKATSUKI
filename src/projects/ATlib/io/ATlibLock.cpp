/**
 * IOオブジェクトに対する排他処理クラス<br>
 * <b>ATlibLock.cpp</b>
 *
 * @author j-fujisaki
 */
#include "ATlib/io/ATlibLock.h"

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param						なし.
 */
//********************************************************************************************
ATLock::ATLock()
	: ml_bLock(false)
{
	/* ハンドルの初期化		*/
	ml_hLockHandle = AT_INVALID_HANDLE;

	createHandle();
}

//********************************************************************************************
/**
 * デストラクタ
 */
//********************************************************************************************
ATLock::~ATLock()
{
	deleteHandle();
}

//********************************************************************************************
/**
 * ロックハンドルの生成
 *
 * @param						なし.
 *
 * @return						なし.
 */
//********************************************************************************************
void ATLock::createHandle()
{
#ifdef PLATFORM_WINDOWS
	/* Mutexオブジェクト作成		*/
	ml_hLockHandle = CreateMutex(0, TRUE, NULL);
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
	/* セマフォ作成					*/
	ml_hLockHandle = semget((key_t)1111, 1, 0666 | IPC_CREAT);
	if (ml_hLockHandle != AT_INVALID_HANDLE) {
		union semuni semunion;
		semunion.nVal = 1;
		if (semctl(ml_hLockHandle, 0, SETVAL, semunion) == -1) {
			TRACE(_T("ATLock createHandle() semctl failed."));
		}
	}
#endif // PLATFORM_LINUX
}

//********************************************************************************************
/**
 * ロックハンドルの削除
 *
 * @param						なし.
 *
 * @return						なし.
 */
//********************************************************************************************
void ATLock::deleteHandle()
{
#ifdef PLATFORM_WINDOWS
	/* Mutexオブジェクトの解放		*/
	if (ml_hLockHandle != AT_INVALID_HANDLE) {
		CloseHandle(ml_hLockHandle);
		ml_hLockHandle = AT_INVALID_HANDLE;
	}
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
	if (ml_hLockHandle != AT_INVALID_HANDLE) {
		union semuni semunion;
		if (semctl(ml_hLockHandle, 0, IPC_RMID, semunion) == -1) {
			TRACE(_T("ATLock deleteHandle() semop failed."));
		}
		ml_hLockHandle = AT_INVALID_HANDLE;
	}
#endif // PLATFORM_LINUX
	ml_bLock = false;
}

//********************************************************************************************
/**
 * 排他処理
 *
 * @param						なし.
 *
 * @return						AT_OK			: 正常
 *								AT_ERR_HANDLE	: 無効なハンドル
 *								AT_ERR_LOCK		: 排他の取得に失敗
 */
//********************************************************************************************
int ATLock::lock()
{
	if (ml_hLockHandle == AT_INVALID_HANDLE) {
		TRACE(_T("ATLock lock() lock handle invalid."));
		return AT_ERR_HANDLE;
	}

#ifdef PLATFORM_WINDOWS
	
	/* 所有権の取得				*/
	if (WaitForSingleObject(ml_hLockHandle, INFINITE) == WAIT_FAILED) {
		TRACE(_T("ATLock lock() waitforsingleobject wait failed."));
		return AT_ERR_LOCK;
	}
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX

	/* セマフォ更新				*/
	ml_stSemb.sem_num = 0;
	ml_stSemb.sem_op = -1;
	ml_stSemb.sem_flg = SEM_UNDO;

	if (semop(ml_hLockHandle, &ml_stSemb, 1) == -1) {
		TRACE(_T("ATLock lock() semop failed."));
		return AT_ERR_LOCK;
	}
#endif // PLATFORM_LINUX

	ml_bLock = true;
	return AT_OK;
}

//********************************************************************************************
/**
 * 排他解除
 *
 * @param						なし.
 *
 * @return						なし.
 */
//********************************************************************************************
void ATLock::unlock()
{
	if (!ml_bLock) {
		return;
	}
#ifdef PLATFORM_WINDOWS
	ReleaseMutex(ml_hLockHandle);
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
	ml_stSemb.sem_op = 1;
	if (semop(ml_hLockHandle, &ml_stSemb, 1) == -1) {
		TRACE(_T("ATLock unlock() semop failed."));
	}
#endif // PLATFORM_LINUX
	ml_bLock = false;
}

//********************************************************************************************
/**
 * ロック可否
 *
 * @param						なし.
 *
 * @return						true	: ロック中
 *								false	: ロック解除
 */
//********************************************************************************************
bool ATLock::isLocked() const
{
	return ml_bLock;
}