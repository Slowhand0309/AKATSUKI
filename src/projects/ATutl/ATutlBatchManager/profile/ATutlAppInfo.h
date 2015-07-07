#ifndef __ATUTLAPPINFO_H__DA2E17D2_3CFD_410F_812D_4D717ECCE339
#define __ATUTLAPPINFO_H__DA2E17D2_3CFD_410F_812D_4D717ECCE339

typedef std::list<TString>			ATAppOptionList;
typedef std::map<TString, TString>	ATAppOptionMap;

/**
 * �o�b�`�A�v���P�[�V�������N���X
 * ATAppInfo.h
 *
 * @author	jf-orange
 */
class ATAppInfo
{
public:
	/**
	 * �R���X�g���N�^
	 */
	ATAppInfo();

	/**
	 * �R�s�[�R���X�g���N�^
	 */
	ATAppInfo(const ATAppInfo &obj);

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATAppInfo();

	/**
	 * �A�v���P�[�V�������̐ݒ�
	 *
	 * @param const TString &szName		�A�v����
	 */
	void setName(const TString &szName);

	/**
	 * �A�v���P�[�V�����ڍאݒ�
	 *
	 * @param const TString &szExplain	�ڍ�
	 */
	void setExplain(const TString &szExplain);

	/**
	 * �A�v���P�[�V�������擾
	 *
	 * @return TString		�A�v���P�[�V������
	 */
	TString getName() const;

	/**
	 * �A�v���P�[�V�����̏ڍ׎擾
	 *
	 * @return TString		�ڍ�
	 */
	TString getExplain() const;

	/**
	 * �I�v�V�����p�����[�^�ǉ�
	 *
	 * @param const TString &szName				�I�v�V�����p�����[�^��
	 * @param const TString &szExplain			�ڍ�
	 */
	void addOption(const TString &szName, const TString &szExplain);

	/**
	 * �I�v�V�����p�����[�^�ꗗ�̎擾
	 *
	 * @param std::list<TString> &optionList	�擾���ꂽ�ꗗ
	 * @return	int
	 */
	int getOptionList(std::list<TString> &optionList);

	/**
	 * �I�v�V�����p�����[�^�̏ڍ׎擾
	 *
	 * @param const TString &optionName			�I�v�V�����p�����[�^��
	 * @return	TString							�ڍ�
	 */
	TString getOptionExplain(const TString &optionName);

	/**
	 * �I�v�V�����p�����[�^�̗L�����擾
	 *
	 * @return	bool		true	: ����
	 *						false	: �Ȃ�
	 */
	bool hasOptionParams() const;

private:
	TString							ml_szAppName;
	TString							ml_szExplain;
	ATAppOptionMap					ml_oOptionMap;
};
#endif // __ATUTLAPPINFO_H__DA2E17D2_3CFD_410F_812D_4D717ECCE339