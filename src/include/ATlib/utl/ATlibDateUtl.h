#ifndef __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75
#define __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75

#include "ATlib/com/ATlibCommon.h"
#include "ATlib/utl/ATlibStringUtl.h"
#include <time.h>

#define DEFAULT_DATE_FORMAT			_T("%Y/%m/%d %H:%M:%S")

class ATDateUtl
{
public:

	/**
	 * ���݂̓����𕶎���Ŏ擾
	 *
	 * @return			���ݓ���
	 */
	static TString getCurrentDate() {
		return getCurrentDate(DEFAULT_DATE_FORMAT);
	};

	/**
	 * ���݂̓����𕶎���Ŏ擾
	 *
	 * @param		TString szFormat	���t�t�H�[�}�b�g������
	 *
	 * @return		���ݓ���
	 */
	static TString getCurrentDate(TString szFormat) {

		time_t		lTime;
		struct tm	*tagNow;
		size_t		uiRet = 0;
		TCHAR		szTime[_MAX_PATH] = {0};

		time(&lTime);
		tagNow = localtime(&lTime);

		if (_tcsftime(szTime, _MAX_PATH, szFormat.c_str(), tagNow) == 0) {
			return TString();
		}
		return TString(szTime);
	};

#ifdef PLATFORM_WINDOWS
/* declaration for windows					*/

	/**
	 * ������SYSTEMTIME���t�H�[�}�b�g������Ŏ擾
	 * 
	 * @param	SYSTEMTIME stSysTime		�V�X�e���^�C��
	 * @param	const TString &szFormat		�t�H�[�}�b�g
	 * @return	TString						������
	 */
	static TString getFormatString(SYSTEMTIME stSysTime, const TString &szFormat) {

		if (ATStringUtl::isEmpty(szFormat)) {
			return AT_EMPTY_STR;
		}

		TCHAR		szValue[_MAX_PATH] = {0};
		_stprintf(szValue, szFormat.c_str(), 
					stSysTime.wYear,   stSysTime.wMonth,
					stSysTime.wDay,    stSysTime.wHour,
					stSysTime.wMinute, stSysTime.wSecond);

		return TString(szValue);
	}

#endif // PLATFORM_WINDOWS

private:
	/**
	 * �C���X�^���X�̍쐬�֎~
	 */
	ATDateUtl();
};
#endif // __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75
