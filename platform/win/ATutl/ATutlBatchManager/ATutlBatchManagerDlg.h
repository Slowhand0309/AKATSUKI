
// ATutlBatchManagerDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "profile/ATutlAppInfo.h"
#include "execute/ATutlExecuteThread.h"
/**
 * CATutlBatchManagerDlg �_�C�A���O
 *
 * @autho jf-orange
 */
class CATutlBatchManagerDlg : public CDialogEx
{
public:
	/**
	 * �R���X�g���N�^
	 */
	CATutlBatchManagerDlg(CWnd* pParent = NULL);

	/**
	 * �f�X�g���N�^
	 */
	virtual ~CATutlBatchManagerDlg();

	// �_�C�A���O �f�[�^
	enum { IDD = IDD_ATUTLBATCHMANAGER_DIALOG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;

private:

	/**
	 * ����������
	 *
	 * @return		int
	 */
	int initialize();

	/**
	 * ���X�g�R���g���[���̏���������
	 *
	 * @return		int
	 */
	int initListCtrl();

	/**
	 * �o�b�`�A�v���P�[�V�������̍X�V
	 *
	 * @param		const TString &szAppName	�A�v����
	 */
	void updateAppInfo(const TString &szAppName);

	/**
	 * ���s���`�F�b�N
	 *
	 * @return		true	: ���s��
	 *				false	: ���s�s��
	 */
	bool validate();

	/**
	 * ���s���̃R�}���h���C���쐬
	 *
	 * @return		�R�}���h���C��������
	 */
	TString createCmdLine();


	CEdit					ml_oStdoutEdit;			/* �W���o�͗pCEdit							*/
	CEdit					ml_oExplainEdit;		/* �A�v���P�[�V�����ڍ�CEdit				*/
	CEdit					ml_oOutputFolderEdit;	/* �o�͗p�t�H���_CEdit						*/
	ATListCtrl				ml_oOptParamListCtrl;
	CComboBox				ml_oApplicationCombo;
	std::list<ATAppInfo>	ml_oAppInfoList;

	HANDLE					ml_hStdOut;				// �W���o�̓n���h��
	HANDLE					ml_hReadStdOut;			// �W���o�͓ǂݍ��݃n���h��

	TString					ml_szOutputDir;			// �o�̓f�B���N�g��
	TString					ml_szLogDir;			// ���O�f�B���N�g��
	TString					ml_szBaseDir;			// ��f�B���N�g��
	ATExecuteThread			*ml_pExecuteThread;		// ���s�X���b�h
	ATAppInfo				ml_oExecuteAppInfo;		// ���s�A�v���P�[�V����
public:
	afx_msg void OnBnClickedButtonFinish();
	afx_msg void OnCbnSelchangeComboModule();	
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonRef();
	
	afx_msg void OnBnClickedButtonHalt();
};
