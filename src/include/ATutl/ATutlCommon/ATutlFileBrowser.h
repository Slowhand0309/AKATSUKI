#ifndef __ATUTLFILEBROWSER_H__ECBB0414_D3CB_446F_A3AD_5677BA1F12BC
#define __ATUTLFILEBROWSER_H__ECBB0414_D3CB_446F_A3AD_5677BA1F12BC
#include "ATlib/com/ATlibCommon.h"

struct FileProperty
{
	TString		m_szFileName;	// �t�@�C������
	TString		m_szAttribute;	// ����
	TString		m_szCreateDate;	// �쐬����
	TString		m_szUpdateDate;	// �X�V����
};

class ATFileBrowser
{
public:

	/**
	 * �R���X�g���N�^
	 */
	ATFileBrowser();

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATFileBrowser();

	/**
	 * �t�H���_�Q��
	 *
	 * @return	�Q�Ɛ�t�H���_�[�p�X
	 *			�L�����Z�����A�G���[���͋󕶎�
	 */
	TString browseFolder();

	/**
	 * �w��f�B���N�g���̃t�@�C���ꗗ�擾
	 *
	 * @param	const TString &szDir				�w��f�B���N�g��
	 * @param	const TString &szExt				�g���q
	 * @param	std::list<FileProperty> &oFileList	�擾�t�@�C�����X�g
	 * @return	int
	 */
	int getFileList(const TString &szDir, 
		const TString &szExt, std::list<FileProperty> &oFileList);

	/**
	 * �t�@�C���̑�����������擾
	 *
	 * @param	const DWORD dwAttribute				����
	 * @return	TString								����������
	 */
	TString getFileArrtibuteStr(const DWORD dwAttribute);

	/**
	 * �t�@�C�������𕶎���ɕϊ�
	 *
	 * @param	const FILETIME stFileTime			�t�@�C������
	 * @return	TString								������
	 */
	TString getFileTimeStr(const FILETIME stFileTime);

private:
	
};
#endif // __ATUTLFILEBROWSER_H__ECBB0414_D3CB_446F_A3AD_5677BA1F12BC