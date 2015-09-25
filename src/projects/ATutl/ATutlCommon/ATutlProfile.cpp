/**
 * INI�t�@�C�������N���X����<br>
 * <b>ATutlProfile.cpp</b>
 *
 * @author slowhand0309
 */
#include "stdafx.h"
#include "ATlib/utl/ATlibSysUtl.h"
#include "ATlib/utl/ATlibStringUtl.h"
#include "ATlib/io/ATlibFile.h"
#include "ATutl/ATutlCommon/ATutlProfile.h"

/* ini�t�@�C�����̃R�����g������		*/
#define COMMENT_MARK				_T(";")

/* ini�t�@�C�����L�[���ڎ��ʕ���		*/
#define KEY_MARK_START				_T("[")
#define KEY_MARK_END				_T("]")

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATProfile::ATProfile()
{
}

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			const TString &szFileName	ini�t�@�C���p�X.
 *
 */
//********************************************************************************************
ATProfile::ATProfile(const TString &szFileName)
{
	this->readProfile(szFileName);
}

//********************************************************************************************
/**
 * �f�X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATProfile::~ATProfile()
{
}

//********************************************************************************************
/**
 * �f�[�^������
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
void ATProfile::clear()
{
	ml_mapList.clear();
}

//********************************************************************************************
/**
 * ini�t�@�C���ǂݍ���
 *
 * @param	const TString &szFileName			ini�t�@�C���p�X
 */
//********************************************************************************************
int ATProfile::readProfile(const TString &szFileName)
{
	int nRet;
	/* �t�@�C���p�X�`�F�b�N		*/
	if (!ATSysUtl::hasPath(szFileName)) {
		return AT_ERR_ARGUMENTS;
	}

	clear();

	/* �t�@�C���I�[�v��			*/
	ATFile oFile;
	nRet = oFile.open(szFileName, OpenMode::OpenMode_TxtReadOnly);
	if (nRet != AT_OK) {
		return nRet;
	}

	TString szBuff;
	TString szKey;
	
	while (!oFile.isEof()) {
		szBuff.clear();

		/* ��s�ǂݍ���		*/
		nRet = oFile.read(szBuff);
		if (nRet == AT_OK) {
			if (ATStringUtl::isEmpty(szBuff) 
				|| szBuff.find(COMMENT_MARK, 0) == 0
				|| szBuff.find(_T("\n"), 0) == 0
				|| szBuff.find(_T("\r"), 0) == 0) {
				continue;
			}

			if (szBuff.find(KEY_MARK_START, 0) == 0) {
				/* �L�[����	���̂��擾	*/
				unsigned int location = szBuff.find(KEY_MARK_END, 1);
				szKey = szBuff.substr(1, location - 1);
				continue;
			}

			if (!szKey.empty()) {
				/* �����̉��s�R�[�h���폜 */
				szBuff = szBuff.substr(0, szBuff.length() - 1);

				ATProfileData::iterator it = ml_mapList.find(szKey);
				if (it != ml_mapList.end()) {
					it->second.push_back(szBuff);
				} else {
					/* �V�K�̃L�[	*/
					std::list<TString> listValues;
					listValues.push_back(szBuff);
					ml_mapList.insert(std::make_pair<TString, std::list<TString>>(szKey, listValues));
				}
			}
		}
	}

	oFile.close();
	ml_szFileName = szFileName;
	return AT_OK;
}

//********************************************************************************************
/**
 * �f�[�^�擾
 *
 * @param	const TString &szKey			�L�[
 * @param	std::list<TString> &listValues	�f�[�^���X�g
 * @return	int
 */
//********************************************************************************************
int ATProfile::getValues(const TString &szKey, std::list<TString> &listValues)
{
	if (ATStringUtl::isEmpty(szKey)) {
		return AT_ERR_ARGUMENTS;
	}

	/* ini�t�@�C�����̃f�[�^���猟��	*/
	ATProfileData::iterator it = ml_mapList.find(szKey);
	if (it == ml_mapList.end()) {
		return AT_ERR_NOTFOUND;
	}
	listValues = it->second;
	return AT_OK;
}