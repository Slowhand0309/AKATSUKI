#ifndef __ATUTLBATCHMANAGERPROFILE_H__D3C7D203_F8CF_44C1_BF07_D8AAABA6CA6E
#define __ATUTLBATCHMANAGERPROFILE_H__D3C7D203_F8CF_44C1_BF07_D8AAABA6CA6E

#include "ATutlAppInfo.h"

class ATBatchManagerProfile : public ATProfile
{
public:
	/**
	 * �R���X�g���N�^
	 */
	ATBatchManagerProfile();

	/**
	 * �R���X�g���N�^
	 * 
	 * @param const TString &szFileName		�t�@�C����
	 */
	ATBatchManagerProfile(const TString &szFileName);

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATBatchManagerProfile();

	/**
	 * ini�t�@�C���ǂݍ���
	 *
	 * @param const TString &szFileName		ini�t�@�C���p�X
	 */
	virtual int readProfile(const TString &szFileName);

	/**
	 * �A�v���P�[�V������񃊃X�g�擾
	 *
	 * @param	std::list<ATAppInfo> &oAppInfoList	�A�v���P�[�V�������X�g
	 * @return	int
	 */
	std::list<ATAppInfo> getAppInfoList();

	/**
	 * ��f�B���N�g���̎擾
	 *
	 * @return TString
	 */
	TString getBaseDir();

	/**
	 * ���O�f�B���N�g���̎擾
	 *
	 * @return TString
	 */
	TString getLogDir();

	/**
	 * �o�̓f�B���N�g���̎擾
	 *
	 * @return	TString
	 */
	TString getOutputDir();

private:

	std::list<ATAppInfo>			ml_oAppInfoList;
};
#endif // __ATUTLBATCHMANAGERPROFILE_H__D3C7D203_F8CF_44C1_BF07_D8AAABA6CA6E