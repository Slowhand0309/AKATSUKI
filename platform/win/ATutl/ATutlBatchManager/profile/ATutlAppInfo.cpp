#include "stdafx.h"
#include "ATutlAppInfo.h"

#include "ATlib/utl/ATlibStringUtl.h"

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATAppInfo::ATAppInfo()
{
}

//********************************************************************************************
/**
 * �R�s�[�R���X�g���N�^
 *
 * @param	const ATAppInfo &obj		�R�s�[��.
 *
 */
//********************************************************************************************
ATAppInfo::ATAppInfo(const ATAppInfo &obj)
{
	ml_szAppName = obj.ml_szAppName;
	ml_szExplain = obj.ml_szExplain;
	ml_oOptionMap = obj.ml_oOptionMap;
}

//********************************************************************************************
/**
 * �f�X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATAppInfo::~ATAppInfo()
{
}

//********************************************************************************************
/**
 * �A�v���P�[�V�������擾
 *
 * @return	TString					�A�v����
 */
//********************************************************************************************
TString ATAppInfo::getName() const
{
	return ml_szAppName;
}

//********************************************************************************************
/**
 * �A�v���P�[�V�����ڍ׎擾
 *
 * @return	TString					�ڍ�
 */
//********************************************************************************************
TString ATAppInfo::getExplain() const
{
	return ml_szExplain;
}

//********************************************************************************************
/**
 * �A�v���P�[�V�������ݒ�
 *
 * @param	const TString &szName	�A�v����
 */
//********************************************************************************************
void ATAppInfo::setName(const TString &szName)
{
	ml_szAppName = szName;
}

//********************************************************************************************
/**
 * �A�v���P�[�V�����ڍאݒ�
 *
 * @param	const TString &szExplain	�ڍ�
 */
//********************************************************************************************
void ATAppInfo::setExplain(const TString &szExplain)
{
	ml_szExplain = szExplain;
}

//********************************************************************************************
/**
 * �I�v�V�����p�����[�^�ǉ�
 *
 * @param	const TString &szName		�I�v�V������
 * @param	const TString &szExplain	�ڍ�
 */
//********************************************************************************************
void ATAppInfo::addOption(const TString &szName, const TString &szExplain)
{
	ml_oOptionMap.insert(ATAppOptionMap::value_type(szName, szExplain));
}

//********************************************************************************************
/**
 * �I�v�V�����p�����[�^���X�g�擾
 *
 * @param	std::list<TString> &optionList			���X�g
 * @return	int
 */
//********************************************************************************************
int ATAppInfo::getOptionList(std::list<TString> &optionList)
{
	if (ml_oOptionMap.size() == 0) {
		/* �I�v�V�����p�����[�^����		*/
		return AT_ERR_NOTFOUND;
	}

	ATAppOptionMap::iterator it;
	for (it = ml_oOptionMap.begin(); it != ml_oOptionMap.end(); ++it) {
		if (ATStringUtl::isNotEmpty(it->first)) {
			optionList.push_back(it->first);
		}
	}
	return AT_OK;
}

//********************************************************************************************
/**
 * �I�v�V�����p�����[�^�ڍׂ̎擾
 *
 * @param	const TString &optionName		�I�v�V�����p�����[�^��
 * @return	TString							�ڍ�
 */
//********************************************************************************************
TString ATAppInfo::getOptionExplain(const TString &optionName)
{
	if (ATStringUtl::isNotEmpty(optionName)) {
		ATAppOptionMap::iterator it = ml_oOptionMap.find(optionName);
		if (it != ml_oOptionMap.end()) {
			return it->second;
		}
	}
	return AT_EMPTY_STR;
}

//********************************************************************************************
/**
 * �I�v�V�����p�����[�^�L���擾
 *
 * @return	bool		true	: ����
 *						false	: �Ȃ�
 */
//********************************************************************************************
bool ATAppInfo::hasOptionParams() const
{
	return !ml_oOptionMap.empty();
}