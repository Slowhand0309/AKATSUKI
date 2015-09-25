/**
 * �o�b�`����������<br>
 * <b>ATbatBatchProc.cpp</b>
 *
 * @author slowhand0309
 */
#include <algorithm>
#include <iterator>
#include "ATbat/base/ATbatBatchProc.h"
#include "ATlib/utl/ATlibSysUtl.h"
#include "ATlib/utl/ATlibStringUtl.h"

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param	const TString &szBatchName		�o�b�`��
 */
//********************************************************************************************
ATBatchProc::ATBatchProc(const TString &szBatchName)
	: ml_szBatchName(szBatchName)
{
	_tsetlocale(LC_ALL, _T("Japanese"));
}

//********************************************************************************************
/**
 * �f�X�g���N�^
 */
//********************************************************************************************
ATBatchProc::~ATBatchProc()
{
}

//********************************************************************************************
/**
 * �o�b�`���s
 *
 * @param	int argc			�����̐�
 * @param	TCHAR *argv[]		����
 * @return	int
 */
//********************************************************************************************
int ATBatchProc::run(int argc, TCHAR *argv[])
{
	int		nRet = -1;
	TString	szBuff;

	do {
		/* �p�����[�^���			*/
		nRet = splitArgs(argc, argv);
		if (nRet < 0) {
			break;
		}

		logAtStart();

		/* ����������				*/
		nRet = initialize();
		if (nRet != AT_OK) {
			/* ������NG					*/
			break;
		}

		/* ���s����					*/
		nRet = execute();

		/* �I������			*/
		finalize();

	} while (0);

	logAtEnd();
	return nRet;
}

//********************************************************************************************
/**
 * �����p�����[�^�̉��
 *  ����
 *     1 : ���s���� YYYYMMDD_HHMMSS (���N���X�Ŏg�p)
 *     2 : ���O�o�͐�
 *     3 : ���s���̃t�@�C�����̏o�͐�
 *     4 : �ڍs�̃p�����[�^�͌p����ŗ��p
 *
 */
//********************************************************************************************
int ATBatchProc::splitArgs(int argc, TCHAR *argv[])
{
	if (argc <= (ARGUMENT_MAX - 1)) {
		tout << _T("argument error!!.") << std::endl;
		return AT_ERR_ARGUMENTS;
	}

	/* ���s���Ԃ̎擾			*/
	ml_szExecTime = argv[1];
	if (ml_szExecTime.empty()) {
		tout << _T("exec time empty!!.") << std::endl;
	}
	
	/* ���O�o�͐�̎擾			*/
	ml_szLogPath = argv[2];
	if (ATStringUtl::isEmpty(ml_szLogPath)) {
		/* ���ݒ�̏ꍇ�͎��s���W���[�������̃p�X��ݒ�		*/
		ml_szLogPath = ATSysUtl::getCurrentPath();
	}

	/* ���s���o�͐�̎擾		*/
	ml_szOutputPath = argv[3];
	if (ATStringUtl::isEmpty(ml_szOutputPath)) {
		/* ���ݒ�̏ꍇ�͎��s���W���[�������̃p�X��ݒ�		*/
		ml_szOutputPath = ATSysUtl::getCurrentPath();
	}

	/* �p�����[�^�̎擾			*/
	for (int ii = ARGUMENT_MAX; ii < argc; ii++) {
		ml_vecParam.push_back(TString(argv[ii]));
	}

	return ml_vecParam.size();
}

//********************************************************************************************
/**
 * �o�b�`�����J�n�����O
 */
//********************************************************************************************
void ATBatchProc::logAtStart()
{
	/* �o�̓��O�t�@�C��������		*/
	TString file = ml_szLogPath + _T("\\") + ml_szBatchName + _T("_") + ml_szExecTime + _T(".log");
	ml_oLogger.setFile(file);

	TString msg = _T("============= batch start [") + ml_szBatchName + _T("] =============");
	ml_oLogger.log(LOG_LEVEL_INFO, msg);

	/* �J�n�������O�o��			*/
	TString execTime =  _T("exec time ==> ") + ml_szExecTime;
	ml_oLogger.log(LOG_LEVEL_INFO, execTime);

	/* ���O�o�͐�				*/
	TString logPath = _T("log path ==> ") + file;
	ml_oLogger.log(LOG_LEVEL_INFO, logPath);

	/* ���s���o�̓p�X			*/
	TString outPath = _T("output path ==> ") + ml_szOutputPath;
	ml_oLogger.log(LOG_LEVEL_INFO, outPath);

	/* �p�����[�^���O�o��		*/
	TString args = _T("parameters ==> ");
	std::vector<TString>::iterator it;
	for (it = ml_vecParam.begin(); it != ml_vecParam.end(); ++it)
	{
		args += *it + _T(", ");
	}
	ml_oLogger.log(LOG_LEVEL_INFO, args);
}

//********************************************************************************************
/**
 * �o�b�`�I�������O
 */
//********************************************************************************************
void ATBatchProc::logAtEnd()
{
	ml_oLogger.log(LOG_LEVEL_INFO, _T("============= batch end ============="));
}