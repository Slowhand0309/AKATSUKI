#ifndef __ATUTLBASETHREAD_H__84CF87E1_0AB6_49C8_A1A5_26A31D0C55DA
#define __ATUTLBASETHREAD_H__84CF87E1_0AB6_49C8_A1A5_26A31D0C55DA

/**
 * �X���b�h���N���X<br>
 * <b>ATutlBaseThread.h</b>
 *
 * @author slowhand0309
 */
class ATBaseThread
{
public:

	/**
	 * �R���X�g���N�^
	 */
	ATBaseThread();

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATBaseThread();

	/**
	 * ����������
	 *
	 * @return	int
	 */
	virtual int initialize();

	/**
	 * �I������
	 */
	virtual void finalize();

	/**
	 * �X���b�h�J�n
	 *
	 * @param int	nPriority		�D��x
	 */
	virtual int startThread(int	nPriority);

	/**
	 * �X���b�h���s����
	 * 
	 * @param LPVOID pParam			this
	 */
	virtual int run(LPVOID pParam) = 0;

protected:
	/**
	 * �X���b�h���Ŏ��s�����֐�
	 */
	static UINT	l_ThreadFunc(LPVOID pParam);

	CWinThread *			ml_pThread;
};
#endif // __ATUTLBASETHREAD_H__84CF87E1_0AB6_49C8_A1A5_26A31D0C55DA