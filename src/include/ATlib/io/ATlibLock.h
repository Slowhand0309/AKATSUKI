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
 * IO�I�u�W�F�N�g�ɑ΂���r�������N���X<br>
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
	 * ���b�N
	 *
	 * @return		AT_OK			: ����
	 *				AT_ERR_HANDLE	: �����ȃn���h��
	 *				AT_ERR_LOCK		: �r���̎擾�Ɏ��s
	 */
	int lock();

	/**
	 * ���b�N����
	 */
	void unlock();

	/**
	 * ���b�N��
	 *
	 * @return		true	: ���b�N��
	 *				false	: ���b�N����
	 */
	bool isLocked() const;

private:

	/**
	 * ���b�N�n���h���쐬
	 */
	void createHandle();

	/**
	 * ���b�N�n���h���폜
	 */
	void deleteHandle();

	bool					ml_bLock;

#ifdef PLATFORM_WINDOWS
	HANDLE					ml_hLockHandle;
#else
	/* �Z�}�t�H�\���̒�`		*/
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
