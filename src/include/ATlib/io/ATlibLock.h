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
 * IOオブジェクトに対する排他処理クラス<br>
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
	 * ロック
	 *
	 * @return		AT_OK			: 成功
	 *				AT_ERR_HANDLE	: 無効なハンドル
	 *				AT_ERR_LOCK		: 排他の取得に失敗
	 */
	int lock();

	/**
	 * ロック解除
	 */
	void unlock();

	/**
	 * ロック可否
	 *
	 * @return		true	: ロック中
	 *				false	: ロック解除
	 */
	bool isLocked() const;

private:

	/**
	 * ロックハンドル作成
	 */
	void createHandle();

	/**
	 * ロックハンドル削除
	 */
	void deleteHandle();

	bool					ml_bLock;

#ifdef PLATFORM_WINDOWS
	HANDLE					ml_hLockHandle;
#else
	/* セマフォ構造体定義		*/
	union semuni {
		int					nVal;
		struct	semid_ds	*buff;
		unsigned short		*array;
		struct	seminfo		*info;
	};

	struct sembuf			ml_stSemb;
	int						ml_hLockHandle;
#endif // PLATFORM_LINUX
};
#endif // __ATLIBLOCK_H__0A06B2FC_821E_4050_99E0_26C285DB2A0A
