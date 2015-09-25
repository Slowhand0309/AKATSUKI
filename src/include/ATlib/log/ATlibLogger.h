#ifndef __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1
#define __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1
#include "ATlib/com/ATlibCommon.h"

#define LOG_LEVEL_NONE				(0x00000000)	/* ���O�o�͖���			*/
#define LOG_LEVEL_INFO				(0x00000001)	/* ��񃍃O�o��			*/
#define LOG_LEVEL_WARN				(0x00000010)	/* �x�����O�o��			*/
#define LOG_LEVEL_ERROR				(0x00000100)	/* �G���[���O�o��		*/
#define LOG_LEVEL_DEBUG				(0x00001000)	/* �f�o�b�O���O�o��		*/

#define LOG_LEVEL	(LOG_LEVEL_INFO | LOG_LEVEL_WARN | LOG_LEVEL_ERROR)

/**
 * ���O�N���X<br>
 * <b>ATlibLogger.h</b>
 *
 * @author slowhand0309
 */
template <class __Printer>
class ATLogger
{
public:
	/**
	 * �R���X�g���N�^<br>
	 * �f�t�H���g�̃��O�o�̓��x��
	 *  INFO , WARN, ERROR
	 */
	ATLogger() {
		ml_nLevel = LOG_LEVEL;
	};

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATLogger() {
	};

	/**
	 * ���O�o�̓��x���̐ݒ�
	 *
	 * @param int level			�o�̓��x��
	 */
	void setLevel(int level) {
		ml_nLevel = level;
	};

	/**
	 * �t�@�C���ݒ�
	 * �g�p����ꍇ�̂�Printer�ŗv����
	 *
	 * @param	const TString &fileName	�t�@�C����
	 */
	void setFile(const TString &fileName) {
		ml_oPrinter.setFile(fileName);
	};

	/**
	 * ���O�o��
	 *
	 * @param	int level				���O�o�̓��x��
	 * @param	const TString &message	���O������
	 */
	 void log(int level, const TString &message) {
	
		if (checkLevel(level)) {
			ml_oPrinter.print(level, message);
		}
	};

private:

	/**
	 * ���O�o�̓��x���`�F�b�N
	 *
	 * @param int level		�`�F�b�N�Ώےl
	 */
	bool checkLevel(int level) {
		if (ml_nLevel & level) {
			return true;
		}
		return false;
	};

	int				ml_nLevel;
	__Printer		ml_oPrinter;
};
#endif // __ATLIBLOGGER_H__18A48F54_69C1_4591_A1BA_2043C8FB51C1