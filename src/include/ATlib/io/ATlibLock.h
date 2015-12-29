#ifndef __ATLIBLOCK_H__0A06B2FC_821E_4050_99E0_26C285DB2A0A
#define __ATLIBLOCK_H__0A06B2FC_821E_4050_99E0_26C285DB2A0A

#include "ATlib/com/ATlibCommon.h"

#ifdef PLATFORM_WINDOWS
#include <typeinfo.h>
#else
#include <typeinfo>
#include <unistd.h>
#include <sys/sem.h>
#endif // PLATFORM

/**
 * Lock/Unlock class<br>
 * <b>ATlibLock.h</b>
 *
 * @author slowhand0309
 */
class ATLock
{
public:

	ATLock();

	virtual ~ATLock();

	/**
	 * Lock.
	 *
	 * @return AT_OK : locked
	 *         AT_ERR_HANDLE : handle error
	 *         AT_ERR_LOCK : lock error
	 */
	int lock();

	/**
	 * Unlock.
	 */
	void unlock();

	/**
	 * Check locked.
	 *
	 * @return true : locked
	 *         false : not lock
	 */
	bool isLocked() const;

private:

	/**
	 * Create handle for lock.
	 */
	void createHandle();

	/**
	 * Delete handle.
	 */
	void deleteHandle();

	bool ml_bLock;

#ifdef PLATFORM_WINDOWS
	HANDLE ml_hLockHandle;
#else
	/* struct seminfo */
	union semuni {
		int nVal;
		struct semid_ds	*buff;
		unsigned short *array;
		struct seminfo *info;
	};

	struct sembuf ml_stSemb;
	int ml_hLockHandle;
#endif // PLATFORM_LINUX
};
#endif // __ATLIBLOCK_H__0A06B2FC_821E_4050_99E0_26C285DB2A0A
