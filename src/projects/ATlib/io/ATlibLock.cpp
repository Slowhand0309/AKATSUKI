/**
 * IO�I�u�W�F�N�g�ɑ΂���r�������N���X<br>
 * <b>ATlibLock.cpp</b>
 *
 * @author j-fujisaki
 */
#include "ATlib/io/ATlibLock.h"

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param						�Ȃ�.
 */
//********************************************************************************************
ATLock::ATLock()
	: ml_bLock(false)
{
	/* �n���h���̏�����		*/
	ml_hLockHandle = AT_INVALID_HANDLE;

	createHandle();
}

//********************************************************************************************
/**
 * �f�X�g���N�^
 */
//********************************************************************************************
ATLock::~ATLock()
{
	deleteHandle();
}

//********************************************************************************************
/**
 * ���b�N�n���h���̐���
 *
 * @param						�Ȃ�.
 *
 * @return						�Ȃ�.
 */
//********************************************************************************************
void ATLock::createHandle()
{
#ifdef PLATFORM_WINDOWS
	/* Mutex�I�u�W�F�N�g�쐬		*/
	ml_hLockHandle = CreateMutex(0, TRUE, NULL);
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
	/* �Z�}�t�H�쐬					*/
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
 * ���b�N�n���h���̍폜
 *
 * @param						�Ȃ�.
 *
 * @return						�Ȃ�.
 */
//********************************************************************************************
void ATLock::deleteHandle()
{
#ifdef PLATFORM_WINDOWS
	/* Mutex�I�u�W�F�N�g�̉��		*/
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
 * �r������
 *
 * @param						�Ȃ�.
 *
 * @return						AT_OK			: ����
 *								AT_ERR_HANDLE	: �����ȃn���h��
 *								AT_ERR_LOCK		: �r���̎擾�Ɏ��s
 */
//********************************************************************************************
int ATLock::lock()
{
	if (ml_hLockHandle == AT_INVALID_HANDLE) {
		TRACE(_T("ATLock lock() lock handle invalid."));
		return AT_ERR_HANDLE;
	}

#ifdef PLATFORM_WINDOWS
	
	/* ���L���̎擾				*/
	if (WaitForSingleObject(ml_hLockHandle, INFINITE) == WAIT_FAILED) {
		TRACE(_T("ATLock lock() waitforsingleobject wait failed."));
		return AT_ERR_LOCK;
	}
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX

	/* �Z�}�t�H�X�V				*/
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
 * �r������
 *
 * @param						�Ȃ�.
 *
 * @return						�Ȃ�.
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
 * ���b�N��
 *
 * @param						�Ȃ�.
 *
 * @return						true	: ���b�N��
 *								false	: ���b�N����
 */
//********************************************************************************************
bool ATLock::isLocked() const
{
	return ml_bLock;
}