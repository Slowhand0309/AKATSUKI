#include "stdafx.h"
#include "ATutlBatchManagerProfile.h"
#include "ATlib/utl/ATlibStringUtl.h"

#define	KEY_APPLICATION			_T("APPLICATION")
#define KEY_BASE_DIR			_T("BASEDIR")
#define KEY_OUT_DIR				_T("OUTDIR")
#define KEY_LOG_DIR				_T("LOGDIR")

#define OPTION_MARK				_T("Option-")
#define OPTION_PARAM_SPLITKEY	_T(",")

#define EXPLAIN_MARK			_T("Explain-")

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATBatchManagerProfile::ATBatchManagerProfile()
	: ATProfile()
{
}

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param	const TString &szFileName		ini�t�@�C���p�X.
 *
 */
//********************************************************************************************
ATBatchManagerProfile::ATBatchManagerProfile(const TString &szFileName)
	: ATProfile(szFileName)
{
}

//********************************************************************************************
/**
 * �f�X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATBatchManagerProfile::~ATBatchManagerProfile()
{
}

//********************************************************************************************
/**
 * ini�t�@�C���ǂݍ���
 *
 * @param		const TString &szFileName		ini�t�@�C���p�X.
 * @return		int
 */
//********************************************************************************************
int ATBatchManagerProfile::readProfile(const TString &szFileName)
{
	int nRet = ATProfile::readProfile(szFileName);
	if (nRet == AT_OK) {

		/* �A�v���P�[�V�������X�g�̎擾		*/
		std::list<TString> appNameList;
		nRet = getValues(KEY_APPLICATION, appNameList);
		if (nRet != AT_OK) {
			return nRet;
		}

		std::list<TString>::iterator it;
		for (it = appNameList.begin(); it != appNameList.end(); ++it) {
			ATAppInfo appInfo;
			appInfo.setName((*it));

			/* �I�v�V�����p�����[�^�擾		*/
			std::list<TString> optionList;
			TString optionKey = OPTION_MARK + *it;
			int nTemp = getValues(optionKey, optionList);
			if (nTemp == AT_OK) {
				/* �I�v�V���������񕪊�		*/
				std::list<TString>::iterator iit;
				for (iit = optionList.begin(); iit != optionList.end(); ++iit) {
					std::list<TString> oValues
						= ATStringUtl::split(*iit, TString(OPTION_PARAM_SPLITKEY));
					appInfo.addOption(oValues.front(), oValues.back());
				}
			}

			/* �ڍׂ̎擾		*/
			std::list<TString> explainList;
			TString explainKey = EXPLAIN_MARK + *it;
			nTemp = getValues(explainKey, explainList);
			if (nTemp == AT_OK) {
				appInfo.setExplain(explainList.front());
			}

			ml_oAppInfoList.push_back(appInfo);
		}
	}
	return nRet;
}

//********************************************************************************************
/**
 * �A�v���P�[�V�������X�g�̎擾
 *
 * @param			�A�v���P�[�V�������X�g.
 *
 */
//********************************************************************************************
std::list<ATAppInfo> ATBatchManagerProfile::getAppInfoList()
{
	return ml_oAppInfoList;
}

//********************************************************************************************
/**
 * ��f�B���N�g���̎擾
 *
 * @param	TString		��f�B���N�g��.
 *
 */
//********************************************************************************************
TString ATBatchManagerProfile::getBaseDir()
{
	std::list<TString> list;
	int nRet = getValues(KEY_BASE_DIR, list);
	if (nRet != AT_OK) {
		return AT_EMPTY_STR;
	}

	/* �擪�ɐݒ肳��Ă���p�X�̂ݍ̗p		*/
	return list.front();
}

//********************************************************************************************
/**
 * ���O�f�B���N�g���̎擾
 *
 * @param	TString		���O�f�B���N�g��.
 *
 */
//********************************************************************************************
TString ATBatchManagerProfile::getLogDir()
{
	std::list<TString> list;
	int nRet = getValues(KEY_LOG_DIR, list);
	if (nRet != AT_OK) {
		return AT_EMPTY_STR;
	}

	/* �擪�ɐݒ肳��Ă���p�X�̂ݍ̗p		*/
	return list.front();
}

//********************************************************************************************
/**
 * �o�̓f�B���N�g���̎擾
 *
 * @param	TString		�o�̓f�B���N�g��.
 *
 */
//********************************************************************************************
TString ATBatchManagerProfile::getOutputDir()
{
	std::list<TString> list;
	int nRet = getValues(KEY_OUT_DIR, list);
	if (nRet != AT_OK) {
		return AT_EMPTY_STR;
	}

	/* �擪�ɐݒ肳��Ă���p�X�̂ݍ̗p		*/
	return list.front();
}