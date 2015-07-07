#ifndef __ATUTLEXECUTETHREAD_H__037950AA_461F_48BB_B391_4651BAF09500
#define __ATUTLEXECUTETHREAD_H__037950AA_461F_48BB_B391_4651BAF09500

class ATExecuteThread : public ATBaseThread
{
public:

	/**
	 * �R���X�g���N�^
	 */
	ATExecuteThread();

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATExecuteThread();

	/**
	 * ���s�p�X�̐ݒ�
	 *
	 * @param	const TString &szCmdLine	���s�p�X 
	 */
	void setCmdLine(const TString &szCmdLine);

	/**
	 * �ʒm��CEdit�̐ݒ�
	 *
	 * @param	CEdit *pEdit				�ʒm��
	 */
	void setNotifyEdit(CEdit *pEdit);

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
	 * �X���b�h���s����
	 * 
	 * @param LPVOID pParam			this
	 */
	virtual int run(LPVOID pParam);

	/**
	 * ���s�v���Z�X�̏I��
	 */
	void stopProccess();

	/**
	 * ���s�v���Z�X�̋����I��
	 */
	void haltProcess();

protected:

	int execute();

	/**
	 * ���s���ʒʒm
	 */
	void notifyExecuteResult();

	/**
	 * �w�蕶�����CEdit�֒ʒm
	 */
	void notifyWindow(const TString &szMessage);

	HANDLE					ml_hStdOut;						// �W���o�̓n���h��
	HANDLE					ml_hReadStdOut;					// �W���o�͓ǂݍ��݃n���h��
	HANDLE					ml_hProcHandle;
	TString					ml_szCmdLine;
	CEdit *					ml_pEdit;
};
#endif // __ATUTLEXECUTETHREAD_H__037950AA_461F_48BB_B391_4651BAF09500