/**
 * Lock class implementation <br>
 * <b>ATlibLock.cpp</b>
 *
 * @author slowhand0309
 */
#include "ATlib/io/ATlibLock.h"

/**
 * Constructor.
 */
ATLock::ATLock()
	: ml_bLock(false)
{
	ml_hLockHandle = AT_INVALID_HANDLE;
	createHandle();
}

/**
 * Destructor.
 */
ATLock::~ATLock()
{
	deleteHandle();
}

/**
 * Create handle for lock.
 */
void ATLock::createHandle()
{
#ifdef PLATFORM_WINDOWS
	/* Create Mutex */
	ml_hLockHandle = CreateMutex(0, TRUE, NULL);
#endif // PLATFORM_WINDOWS

#if defined(PLATFORM_LINUX) || defined(PLATFORM_IOS)
	/* Create semaphore */
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

/**
 * Delete handle.
 */
void ATLock::deleteHandle()
{
#ifdef PLATFORM_WINDOWS
	/* Check Mutex */
	if (ml_hLockHandle != AT_INVALID_HANDLE) {
		CloseHandle(ml_hLockHandle);
		ml_hLockHandle = AT_INVALID_HANDLE;
	}
#endif // PLATFORM_WINDOWS

#if defined(PLATFORM_LINUX) || defined(PLATFORM_IOS)
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

/**
 * Lock.
 *
 * @return AT_OK : locked
 *         AT_ERR_HANDLE : handle error
 *         AT_ERR_LOCK : lock error
 */
int ATLock::lock()
{
	if (ml_hLockHandle == AT_INVALID_HANDLE) {
		TRACE(_T("ATLock lock() lock handle invalid."));
		return AT_ERR_HANDLE;
	}

#ifdef PLATFORM_WINDOWS

	/* Wait */
	if (WaitForSingleObject(ml_hLockHandle, INFINITE) == WAIT_FAILED) {
		TRACE(_T("ATLock lock() waitforsingleobject wait failed."));
		return AT_ERR_LOCK;
	}
#endif // PLATFORM_WINDOWS

#if defined(PLATFORM_LINUX) || defined(PLATFORM_IOS)

	/* semaphore lock */
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

/**
 * Unlock.
 */
void ATLock::unlock()
{
	if (!ml_bLock) {
		return;
	}
#ifdef PLATFORM_WINDOWS
	ReleaseMutex(ml_hLockHandle);
#endif // PLATFORM_WINDOWS

#if defined(PLATFORM_LINUX) || defined(PLATFORM_IOS)
	ml_stSemb.sem_op = 1;
	if (semop(ml_hLockHandle, &ml_stSemb, 1) == -1) {
		TRACE(_T("ATLock unlock() semop failed."));
	}
#endif // PLATFORM_LINUX
	ml_bLock = false;
}

/**
 * Check locked.
 *
 * @return true : locked
 *         false : not lock
 */
bool ATLock::isLocked() const
{
	return ml_bLock;
}
