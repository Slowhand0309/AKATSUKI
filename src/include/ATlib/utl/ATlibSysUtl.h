#ifndef __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B
#define __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B

#include "ATlib/com/ATlibCommon.h"

class ATSysUtl
{
public:

	/**
	 * ���W���[�����̎擾
	 *
	 * @return	TString		���W���[����
	 */
	static TString getModuleName() {

		TString		strRet = _T("");
		TCHAR	szFullPath[_MAX_PATH] = {0};
		TCHAR	szFname[_MAX_FNAME] = {0};

#ifdef PLATFORM_WINDOWS
		// ���݂̃��W���[�������܂߂����S�t���p�X���擾
		GetModuleFileName(GetModuleHandle(NULL), szFullPath, _MAX_PATH);

		// �p�X, ���W���[����, �g���q, ���ꂼ��ɕ�������
		_tsplitpath_s(szFullPath, NULL, 0, NULL, 0, szFname, _MAX_FNAME, NULL, 0);
#else
#endif // PLATFORM_WINDOWS

		strRet = TString(szFname);
		return strRet;
	};

	/**
	 * ���݂̎��s���W���[���̃p�X���擾
	 *
	 * @return TString			�p�X
	 */
	static TString getCurrentPath() {

		TCHAR	szFullPath[_MAX_PATH] = {0};
		TCHAR	szDir[_MAX_DIR] = {0};
		TCHAR	szFname[_MAX_FNAME] = {0};
		TCHAR	szExt[_MAX_EXT] = {0};

#ifdef PLATFORM_WINDOWS
		// ���݂̃��W���[�������܂߂����S�t���p�X���擾
		GetModuleFileName(GetModuleHandle(NULL), szFullPath, _MAX_PATH);

		// �p�X, ���W���[����, �g���q, ���ꂼ��ɕ�������
		_tsplitpath_s( szFullPath, NULL, 0, szDir, _MAX_DIR
			, szFname, _MAX_FNAME, szExt, _MAX_EXT );

#else
#endif // PLATFORM_WINDOWS
		return TString(szDir);
	};

	/**
	 * �p�X�����񂩂�g���q���擾<br>
	 * �g���q�����݂��Ȃ��ꍇ�󕶎���Ԃ�
	 * 
	 * @param const TString &szPath		�p�X������
	 * @return TString					�g���q
	 */
	static TString getExtension(const TString &szPath) {

		TString		szExtension = _T("");
		unsigned int uiPoint = 0;

		if(szPath.empty()){
			return _T(""); 
		}

		unsigned int uiStrLen = szPath.length();
		while(szPath[uiPoint] != _T('\0')){

			/* �g���q�������������_�Ń��[�v�𔲂���	*/
			if(szPath[uiPoint] == _T('.')){
				break;
			}
			++uiPoint;
			
			if(static_cast<unsigned int>(szPath.length()) <= uiPoint){
				/* �Ō�܂Ŋg���q��������Ȃ������ꍇ		*/
				return _T("");
			}
		}

		szExtension = szPath.substr(++uiPoint);
		return szExtension;
	};

	/**
	 * �p�X�̗L�����`�F�b�N
	 *
	 * @param const TString &szPath		�p�X
	 * @return		true	: �L��
	 *				false	: ����
	 */
	static bool hasPath(const TString &szPath) {

		int		iRet = 0;
		struct _stat tagStat;

		if(szPath.empty()){
			return false;
		}
	
		/* �w�肳�ꂽ�t�@�C���p�X�̏����擾	*/
		iRet = _tstat(szPath.c_str(), &tagStat);
		if(iRet != 0){
			if(errno == ENOENT){
				/* �t�@�C�������݂��Ȃ�		*/
			} else if(errno == EINVAL){
				/* _tstat �G���[			*/
			}
			return false;
		}
		return true;
	}

private:
	ATSysUtl();
};
#endif // __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B