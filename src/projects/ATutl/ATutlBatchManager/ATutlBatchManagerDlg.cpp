
// ATutlBatchManagerDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ATutlBatchManager.h"
#include "ATutlBatchManagerDlg.h"
#include "afxdialogex.h"

#include "ATlib/utl/ATlibStringUtl.h"
#include "ATutl/ATutlCommon/ATutlFileBrowser.h"
#include "profile/ATutlBatchManagerProfile.h"
#include "ATlib/utl/ATlibSysUtl.h"
#include "ATlib/utl/ATlibDateUtl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* INI�t�@�C������					*/
#define	INIFILE_PATH				_T("test.ini")

/* ----- ini file define ----- */
#define	KEY_APPLICATION				_T("APPLICATION")
#define KEY_BASE_DIR				_T("BASE_DIR")
#define KEY_OUT_DIR					_T("OUT_DIR")
#define KEY_LOG_DIR					_T("LOG_DIR")

/* ----- ctrl list define ----- */
#define LISTCTRL_HEADER_OPTION		_T("�I�v�V����")
#define LISTCTRL_HEADER_EXPLAIN		_T("����")

#define EXECUTE_DATETIME_FMT		_T("%Y%m%d_%H%M%S")

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CATutlBatchManagerDlg �_�C�A���O




CATutlBatchManagerDlg::CATutlBatchManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CATutlBatchManagerDlg::IDD, pParent)
	, ml_pExecuteThread(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CATutlBatchManagerDlg::~CATutlBatchManagerDlg()
{
	AT_SAFE_DELETE(ml_pExecuteThread);
}

void CATutlBatchManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODULE, ml_oApplicationCombo);
	DDX_Control(pDX, IDC_LIST_OPT_PARAM, ml_oOptParamListCtrl);
	DDX_Control(pDX, IDC_EDIT_EXPLAIN, ml_oExplainEdit);
	DDX_Control(pDX, IDC_EDIT_OUTDIR, ml_oOutputFolderEdit);
	DDX_Control(pDX, IDC_EDIT_STDOUT, ml_oStdoutEdit);
}

BEGIN_MESSAGE_MAP(CATutlBatchManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_FINISH, &CATutlBatchManagerDlg::OnBnClickedButtonFinish)
	ON_CBN_SELCHANGE(IDC_COMBO_MODULE, &CATutlBatchManagerDlg::OnCbnSelchangeComboModule)
	ON_BN_CLICKED(ID_BUTTON_RUN, &CATutlBatchManagerDlg::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_REF, &CATutlBatchManagerDlg::OnBnClickedButtonRef)
	ON_BN_CLICKED(IDC_BUTTON_HALT, &CATutlBatchManagerDlg::OnBnClickedButtonHalt)
END_MESSAGE_MAP()


// CATutlBatchManagerDlg ���b�Z�[�W �n���h���[

BOOL CATutlBatchManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	/* ����������							*/
	if (initialize() != AT_OK) {
		/* ���������s�̏ꍇ�̓A�v���I��		*/
		CDialogEx::OnCancel();
	}

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

//********************************************************************************************
/**
 * ����������
 *
 * @return	int
 */
//********************************************************************************************
int CATutlBatchManagerDlg::initialize() 
{
	/* INI�t�@�C���ǂݍ���		*/
	ATBatchManagerProfile profile;
	int nRet = profile.readProfile(INIFILE_PATH);
	if (nRet != AT_OK) {
		ATMessageBoxError(_T("INI�t�@�C���̓ǂݍ��݂Ɏ��s���܂���"));
		return nRet;
	}

	/* �A�v���P�[�V�������X�g�擾	*/
	ml_oAppInfoList = profile.getAppInfoList();
	if (ml_oAppInfoList.size() == 0) {
		ATMessageBoxError(_T("�A�v���P�[�V�����ꗗ�̓ǂݍ��݂Ɏ��s���܂���"));
		return AT_ERR_NOTFOUND;
	}

	/* ���W���[���R���{�{�b�N�X�֐ݒ�	*/
	std::list<ATAppInfo>::iterator it;
	for (it = ml_oAppInfoList.begin(); it != ml_oAppInfoList.end(); ++it) {
		ml_oApplicationCombo.AddString(T2CString(it->getName()));
	}

	/* ��f�B���N�g���̎擾			*/
	ml_szBaseDir = profile.getBaseDir();
	if (ATStringUtl::isEmpty(ml_szBaseDir)) {
		ATMessageBoxError(_T("�ݒ�t�@�C���Ɋ�f�B���N�g�����ݒ肳��Ă��܂���"));
		return AT_ERR_SETTINGS;
	}

	/* ���O�f�B���N�g���̎擾			*/
	ml_szLogDir = profile.getLogDir();

	/* �o�̓f�B���N�g���̐ݒ�			*/
	ml_szOutputDir = profile.getOutputDir();
	if (ATStringUtl::isEmpty(ml_szOutputDir)) {
		ATMessageBoxError(_T("�ݒ�t�@�C���ɏo�̓f�B���N�g�����ݒ肳��Ă��܂���"));
		return AT_ERR_SETTINGS;
	}
	ml_oOutputFolderEdit.SetWindowText(ml_szOutputDir.c_str());

	nRet = initListCtrl();
	return nRet;
}

//********************************************************************************************
/**
 * ���X�g�R���g���[������������
 *
 * @return	int
 */
//********************************************************************************************
int CATutlBatchManagerDlg::initListCtrl()
{
	/* �I�v�V�����p�����[�^���X�g������		*/
	ml_oOptParamListCtrl.setGridLineStyle();
	ml_oOptParamListCtrl.setCheckBoxStyle();
	
	ml_oOptParamListCtrl.insertHeadItem(0, CString(LISTCTRL_HEADER_OPTION), 60);
	ml_oOptParamListCtrl.insertHeadItem(1, CString(LISTCTRL_HEADER_EXPLAIN), 200);

	return AT_OK;
}

//********************************************************************************************
/**
 * ���X�g�R���g���[������������
 *
 * @return	int
 */
//********************************************************************************************
void CATutlBatchManagerDlg::updateAppInfo(const TString &szAppName)
{
	if (ATStringUtl::isEmpty(szAppName)) {
		return;
	}

	/* �e�R���g���[��������		*/
	ml_oOptParamListCtrl.DeleteAllItems();
	ml_oExplainEdit.SetWindowText(AT_EMPTY_STR);

	std::list<ATAppInfo>::iterator it;
	for (it = ml_oAppInfoList.begin(); it != ml_oAppInfoList.end(); ++it) {
		if (szAppName == it->getName()) {
			/* �ڍׂ̍X�V									*/
			ml_oExplainEdit.SetWindowText(T2CString(it->getExplain()));

			/* �ΏۃA�v���P�[�V�����̃I�v�V�����ꗗ���X�V	*/
			if (!it->hasOptionParams()) {
				continue;
			}
			std::list<TString> optionList;
			if (it->getOptionList(optionList) == AT_OK) {
				/* �I�v�V�����ꗗ�����X�g�֐ݒ�		*/
				int index = 0;
				std::list<TString>::iterator iit;
				for (iit = optionList.begin(); iit != optionList.end(); ++iit, index++) {
					ml_oOptParamListCtrl.setListData(index, 0, T2CString((*iit)));
					/* �I�v�V�����̐���		*/
					TString szExplain = it->getOptionExplain((*iit));
					if (ATStringUtl::isNotEmpty(szExplain)) {
						ml_oOptParamListCtrl.setListData(index, 1, T2CString(szExplain));
					}
				}
			}
		}
	}
}

void CATutlBatchManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CATutlBatchManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CATutlBatchManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//********************************************************************************************
/**
 * ���s���`�F�b�N����
 *
 * @return	bool		true	: ���s��
 *						false	: ���s�s��
 */
//********************************************************************************************
bool CATutlBatchManagerDlg::validate()
{
	int nIdx = ml_oApplicationCombo.GetCurSel();
	if (nIdx < 0) {
		/* �A�v�����I��			*/
		ATMessageBoxWarning(_T("���s�A�v���P�[�V�������I������Ă��܂���"));
		return false;
	}

	int nCount = 0;
	std::list<ATAppInfo>::iterator it;
	for (it = ml_oAppInfoList.begin(); it != ml_oAppInfoList.end(); it++, nCount++) {
		if (nIdx == nCount) {
			break;
		}
	}

	if (it->hasOptionParams()) {
		/* �K�{�I�v�V�����`�F�b�N	*/
	}

	/* ���s�A�v���P�[�V�������݃`�F�b�N		*/
	TString szCmdLine = ml_szBaseDir + _T("\\") + it->getName();
	if (!ATSysUtl::hasPath(szCmdLine)) {
		TString msg = _T("���s�A�v���P�[�V�����̃p�X���s���ł�\n�u") + szCmdLine + _T("�v");
		ATMessageBoxWarning(msg.c_str());
		return false;
	}

	ml_oExecuteAppInfo = *it;
	return true;
}

//********************************************************************************************
/**
 * �A�v���P�[�V�����I����
 *
 * @return	�Ȃ�
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnCbnSelchangeComboModule()
{
	/* ���݂̐ݒ�l���擾	*/
	CString szAppName;
	ml_oApplicationCombo.GetLBText(ml_oApplicationCombo.GetCurSel(), szAppName);

	/* �ڍׂƃI�v�V�����ꗗ���X�V			*/
	updateAppInfo(C2TString(szAppName));
}

//********************************************************************************************
/**
 * �u�I���v�{�^��������
 *
 * @return	�Ȃ�
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnBnClickedButtonFinish()
{
	CDialogEx::OnCancel();
}

//********************************************************************************************
/**
 * �u���s�v�{�^��������
 *
 * @return	�Ȃ�
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnBnClickedButtonRun()
{
	int nRet = ATMessageBoxQuestion(_T("�A�v���P�[�V���������s���Ă���낵���ł����H"));
	if (nRet == IDNO) {
		/* ���s�L�����Z��		*/
		return;
	}

	if (!validate()) {
		/* ���s���`�F�b�NNG		*/
		return;
	}

	TRACE(_T("execute app name : %ls \n"), ml_oExecuteAppInfo.getName().c_str());
	TRACE(_T("execute app explain : %ls \n"), ml_oExecuteAppInfo.getExplain().c_str());

	AT_SAFE_DELETE(ml_pExecuteThread);

	/* �R�}���h���C���쐬	*/
	TString szCmdLine = createCmdLine();

	ml_pExecuteThread = new ATExecuteThread();
	ml_pExecuteThread->setCmdLine(szCmdLine);
	ml_pExecuteThread->setNotifyEdit(&ml_oStdoutEdit);

	ml_pExecuteThread->startThread(0);
}

//********************************************************************************************
/**
 * �R�}���h���C��������̍쐬
 *
 * @return	�R�}���h���C��������
 */
//********************************************************************************************
TString CATutlBatchManagerDlg::createCmdLine()
{
	CString szBuff;

	/* �R�}���h���C���쐬	*/
	TString szCmdLine = ml_szBaseDir + _T("\\") + ml_oExecuteAppInfo.getName();

	// 1: ���s����
	TString szDate = ATDateUtl::getCurrentDate(EXECUTE_DATETIME_FMT);

	// 2: ���O�o�͐�

	// 3: �o�͐�
	ml_oOutputFolderEdit.GetWindowText(szBuff);
	ml_szOutputDir = szBuff;

	szCmdLine += _T(" \"") + szDate + _T("\" \"") + ml_szLogDir + _T("\" \"") + ml_szOutputDir + _T("\"");

	/* �I�v�V�����p�����[�^�̐ݒ�		*/
	std::list<CString> oCheckList;
	ml_oOptParamListCtrl.getCheckColumnData(oCheckList);

	std::list<CString>::iterator it;
	for (it = oCheckList.begin(); it != oCheckList.end(); ++it) {
		szCmdLine += _T(" ") + *it;
	}

	TRACE(_T("execute app cmdline : %ls \n"), szCmdLine.c_str());

	return szCmdLine;
}

//********************************************************************************************
/**
 * �o�͐�u�Q�Ɓv�{�^��������
 *
 * @return	�Ȃ�
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnBnClickedButtonRef()
{
	ATFileBrowser oBrowser;
	TString path = oBrowser.browseFolder();

	if (ATStringUtl::isNotEmpty(path)) {
		ml_oOutputFolderEdit.SetWindowText(path.c_str());
	}
}

//********************************************************************************************
/**
 * �u�o�b�`�����I���v�{�^��������
 *
 * @return	�Ȃ�
 */
//********************************************************************************************
void CATutlBatchManagerDlg::OnBnClickedButtonHalt()
{
	if (ml_pExecuteThread != NULL) {
		ml_pExecuteThread->haltProcess();
	}
}