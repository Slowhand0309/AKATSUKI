#ifndef __ATUTLPROFILE_H__19DCC682_5461_4291_8D3E_DBA249A2457B
#define __ATUTLPROFILE_H__19DCC682_5461_4291_8D3E_DBA249A2457B
#include "ATlib/com/ATlibCommon.h"

typedef std::map<TString, std::list<TString>> ATProfileData;

/**
 * INI�t�@�C�������N���X<br>
 * <b>ATutlProfile.h</b>
 *
 * @author slowhand0309
 */
class ATProfile
{
public:
	/**
	 * �R���X�g���N�^
	 */
	ATProfile();

	/**
	 * �R���X�g���N�^
	 *
	 * @param const TString &szFileName		ini�t�@�C���p�X
	 */
	ATProfile(const TString &szFileName);

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATProfile();
	
	/**
	 * �f�[�^������
	 */
	void clear();

	/**
	 * ini�t�@�C���ǂݍ���
	 *
	 * @param const TString &szFileName		ini�t�@�C���p�X
	 */
	virtual int readProfile(const TString &szFileName);

	/**
	 * �f�[�^�擾
	 *
	 * @param const TString &szKey				�L�[
	 * @param std::list<TString> &listValues	�f�[�^���X�g
	 */
	int getValues(const TString &szKey, std::list<TString> &listValues);

protected:
	TString				ml_szFileName;
	ATProfileData		ml_mapList;
};
#endif // __ATUTLPROFILE_H__19DCC682_5461_4291_8D3E_DBA249A2457B