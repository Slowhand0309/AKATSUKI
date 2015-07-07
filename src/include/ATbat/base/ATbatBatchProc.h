#ifndef __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF
#define __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/utl/ATlibDateUtl.h"
#include "ATlib/log/ATlibLogger.h"
#include "ATlib/log/ATlibSysPrinter.h"

#define ARGUMENT_MAX		(4)

/**
 * �o�b�`�pPrinter�N���X<br>
 * <b>ATlibBatchProc.h</b>
 *
 * @author j-fujisaki
 */
class ATBatchPrinter : public ATPrinter
{
public:

	/**
	 * �R���X�g���N�^
	 */
	ATBatchPrinter() {};

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATBatchPrinter() {
		ml_ofstream.close();
	};

	/**
	 * ���O�t�@�C���̐ݒ�
	 *
	 * @param const TString &fileName	���O�t�@�C����
	 */
	virtual void setFile(const TString &fileName) {
		ml_ofstream.open(fileName.c_str());
	};

	/**
	 * ���O�o��
	 *
	 * @param int level					���O�o�̓��x��
	 * @param const TString &message	�o�͕�����
	 */
	virtual void print(int level, const TString &message) {
		TString strLevel;
		switch (level) {
			case LOG_LEVEL_INFO:
				strLevel = _T(" <I> ");
				break;
			case LOG_LEVEL_WARN:
				strLevel = _T(" <W> ");
				break;
			case LOG_LEVEL_ERROR:
				strLevel = _T(" <E> ");
				break;
			case LOG_LEVEL_DEBUG:
				strLevel = _T(" <D> ");
				break;
			default:
				break;
		}

		TString date = ATDateUtl::getCurrentDate();
		tout << date.c_str() << strLevel.c_str() << message.c_str() << std::endl;
		if (ml_ofstream.is_open()) {
			ml_ofstream << date.c_str() << strLevel.c_str() << message.c_str() << std::endl; 
		}
	};

private:
	tofstream ml_ofstream;
};

/**
 * �o�b�`�������N���X<br>
 * <b>ATlibBatchProc.h</b>
 *
 * @author j-fujisaki
 */
class ATBatchProc
{
public:

	/**
	 * �R���X�g���N�^
	 *
	 * @param const TString &szBatchName	�o�b�`��
	 */
	ATBatchProc(const TString &szBatchName);

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATBatchProc();

	/**
	 * �o�b�`���s
	 *
	 * @param int argc				�����̐�
	 * @param TCHAR *argv[]			����
	 * @return int
	 */
	virtual int run(int argc, TCHAR *argv[]);

protected:

	/**
	 * ����������<br>
	 * �������z�֐�
	 *
	 * @return int
	 */
	virtual int initialize() = 0;

	/**
	 * ���s����<br>
	 * �������z�֐�
	 *
	 * @return int
	 */
	virtual int execute() = 0;

	/**
	 * �I������<br>
	 * �������z�֐�
	 */
	virtual void finalize() = 0;

	/**
	 * ������͏���
	 *
	 * @param int argc				�����̐�
	 * @param TCHAR *argv[]			����
	 * @return int					��͌�̈����̐�
	 */
	virtual int splitArgs(int argc, TCHAR *argv[]);

	/**
	 * �o�b�`�J�n�����O
	 */
	virtual void logAtStart();

	/**
	 * �o�b�`�I�������O
	 */
	virtual void logAtEnd();

	TString						ml_szBatchName;
	TString						ml_szExecTime;
	TString						ml_szLogPath;
	TString						ml_szOutputPath;
	std::vector<TString>		ml_vecParam;
	ATLogger<ATBatchPrinter>	ml_oLogger;
};
#endif // __ATBATBATCHPROC_H__EF114B68_0F81_4D07_ABC8_EFF9CC8E36CF