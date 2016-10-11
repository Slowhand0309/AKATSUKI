/**
 * �t�@�C���u���E�U�N���X����<br>
 * <b>ATutlFileBrowser.cpp</b>
 *
 * @author slowhand0309
 */
#include "stdafx.h"
#include "ATlib/utl/ATlibDateUtl.h"
#include "ATutlFileBrowser.h"

#define BROWSE_FOLDER_TITLE				_T("�t�H���_�̑I��")
#define	FILE_TIME_FORMAT				_T("%d/%d/%d %d:%d:%d")

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATFileBrowser::ATFileBrowser()
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
ATFileBrowser::~ATFileBrowser()
{
}

//********************************************************************************************
/**
 * �t�H���_�[�Q��
 *
 * @param			�Ȃ�.
 * @return			�Q�ƃp�X
 *					�G���[����L�����Z�����͋󕶎�
 */
//********************************************************************************************
TString ATFileBrowser::browseFolder()
{
	BROWSEINFO			stBrowseInfo;
	LPITEMIDLIST		pIdList;
	TCHAR				szPath[_MAX_PATH] = {0};

	/* �t�H���_�I���_�C�A���O�̐ݒ�		*/
	stBrowseInfo.hwndOwner             = AfxGetMainWnd()->m_hWnd;	// �e�E�C���h�E�̃n���h��
	stBrowseInfo.pidlRoot              = NULL;						// �f�t�H���g�p�X�iNULL�F�f�X�N�g�b�v�j
	stBrowseInfo.pszDisplayName        = szPath;					// �I�����ꂽ�p�X�󂯎��p�o�b�t�@
	stBrowseInfo.lpszTitle             = BROWSE_FOLDER_TITLE;		// �_�C�A���O�ɕ\������^�C�g�� 
	stBrowseInfo.ulFlags               = BIF_RETURNONLYFSDIRS;
	stBrowseInfo.lpfn                  = NULL;
	stBrowseInfo.lParam                = (LPARAM)0;

	//�t�H���_�I���_�C�A���O�@�\��
	pIdList = ::SHBrowseForFolder(&stBrowseInfo);
	if(pIdList == NULL){
		/*	�L�����Z����		*/
		return AT_EMPTY_STR;
	} else {
		/*	�I�����ꂽ�ꍇ		*/
		if(!::SHGetPathFromIDList(pIdList, szPath)){
			/*	�G���[��		*/
			return AT_EMPTY_STR;
		}

		/* pIdList�̃|�C���g���Ă��郁�������J��	*/
		::CoTaskMemFree(pIdList);
	}

	return TString(szPath);
}

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
int ATFileBrowser::getFileList(const TString &szDir, 
		const TString &szExt, std::list<FileProperty> &oFileList)
{
	HANDLE				hSearch;
	WIN32_FIND_DATA		fd;
	TString				szFileName = szDir + _T("\\*.") + szExt;

	hSearch = FindFirstFile(szFileName.c_str(), &fd);
	if(hSearch == INVALID_HANDLE_VALUE){
		return AT_ERR_HANDLE;
	}

	/* �t�@�C���������[�v		*/
	while (1) {
		FileProperty	oProperty;

		/* �t�@�C�������擾		*/
		TString szBuff(fd.cFileName);
		if (ATStringUtl::isEmpty(szBuff)) {
			continue;
		}

		/* �t�@�C�����̂��u.�v���u..�v�̏ꍇ�̓X�L�b�v	*/
		if (ATStringUtl::contains(szBuff, _T(".")) 
			|| ATStringUtl::contains(szBuff, _T(".."))) {
				continue;
		}

		/* �����A�쐬�����A�X�V�������擾	*/
		TString szAttribute = getFileArrtibuteStr(fd.dwFileAttributes);
		TString szCreateDate = getFileTimeStr(fd.ftCreationTime);
		TString szUpdateDate = getFileTimeStr(fd.ftLastWriteTime);

		oProperty.m_szFileName = szBuff;
		oProperty.m_szAttribute = szAttribute;
		oProperty.m_szCreateDate = szCreateDate;
		oProperty.m_szUpdateDate = szUpdateDate;

		oFileList.push_back(oProperty);

		// ���̃t�@�C���֐i��
		if(!FindNextFile(hSearch, &fd)){
			if(GetLastError() == ERROR_NO_MORE_FILES){
				break;
			} else {
				FindClose( hSearch );
				return AT_ERR_HANDLE;
			}
		}
	}

	FindClose(hSearch);
	return AT_OK;
}

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
TString ATFileBrowser::getFileArrtibuteStr(const DWORD dwAttribute)
{
	TString szValue = _T("");

	if(dwAttribute & FILE_ATTRIBUTE_DIRECTORY){
		szValue = _T("�f�B���N�g��");
	} else if(dwAttribute & FILE_ATTRIBUTE_ARCHIVE){
		szValue = _T("�A�[�J�C�u");
	} else if(dwAttribute & FILE_ATTRIBUTE_COMPRESSED){
		szValue = _T("���k�t�@�C��");
	} else if(dwAttribute & FILE_ATTRIBUTE_HIDDEN){
		szValue = _T("�B���t�@�C��");
	} else if(dwAttribute & FILE_ATTRIBUTE_NORMAL){
		szValue = _T("�t�@�C��");
	} else if(dwAttribute & FILE_ATTRIBUTE_READONLY){
		szValue = _T("�ǎ��p");
	} else if(dwAttribute & FILE_ATTRIBUTE_SYSTEM){
		szValue = _T("�V�X�e���t�@�C��");
	} else if(dwAttribute & FILE_ATTRIBUTE_TEMPORARY){
		szValue = _T("�ꎞ�t�@�C��");
	} else {
		szValue = _T("���̑�");
	}
	return szValue;
}

//********************************************************************************************
/**
 * �t�@�C�������̓����𕶎���ɕϊ�����
 *
 * @param			����������.
 *
 */
//********************************************************************************************
TString ATFileBrowser::getFileTimeStr(const FILETIME stFileTime)
{
	SYSTEMTIME stSystemTime;
	/* �V�X�e�����Ԃɕϊ�	*/
	if(FileTimeToSystemTime(&stFileTime, &stSystemTime) == FALSE){
		return AT_EMPTY_STR;
	}

	/* �t�H�[�}�b�g������Ƃ��ĕԋp		*/
	return ATDateUtl::getFormatString(stSystemTime, FILE_TIME_FORMAT);
}