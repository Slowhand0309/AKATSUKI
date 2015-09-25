#ifndef __ATLIBSTRINGUTL_H__3B42A968_727A_46F7_8528_2E33B66B9152
#define __ATLIBSTRINGUTL_H__3B42A968_727A_46F7_8528_2E33B66B9152

#include "ATlib/com/ATlibCommon.h"

/**
 * �������[�e�B���e�B�N���X<br>
 * <b>ATlibStringUtl.h</b>
 *
 * @author slowhand0309
 */
class ATStringUtl
{
public:

	/**
	 * �󔻒�
	 *
	 * @param const TString &szValue ���蕶����
	 * @return		true	: ��
	 *				false	: ��łȂ�
	 */
	static bool isEmpty(const TString &szValue) {
		if (&szValue == NULL) {
			return true;
		}
		return szValue.empty();
	};

	/**
	 * Not�󔻒�
	 *
	 * @param const TString &szValue ���蕶����
	 * @return		true	: ��łȂ�
	 *				false	: ��
	 */
	static bool isNotEmpty(const TString &szValue) {
		return !ATStringUtl::isEmpty(szValue);
	}

	/**
	 * ������̐��l�`�F�b�N
	 *
	 * @param const TString &szValue	���蕶����
	 * @return		true	: ���l
	 *				false	: ���l�łȂ�
	 */
	static bool isDigit(const TString &szValue) {

		if (ATStringUtl::isEmpty(szValue)) {
			return false;
		}

		char szBuff[_MAX_PATH] = {0};
		const TCHAR *szTemp = szValue.c_str();
		int nSize = szValue.length();

#ifdef _UNICODE
		/* �}���`�o�C�g�����֕ϊ�		*/
		nSize = ATStringUtl::wide2Multi(szTemp, szBuff, nSize);
#endif
		for (int i = 0; i < nSize; i++) {
			char at = szBuff[i];
			if (!ATStringUtl::isDigit(at)) {
				return false;
			}
		}
		return true;
	}

	/**
	 * ���l�`�F�b�N
	 *
	 * @param const cahr at			���蕶��
	 * @return						true	: ���l
	 *								false	: ���l�ȊO
	 */
	static bool isDigit(const char at) {

		if (isdigit(at)) {
			return true;
		}
		return false;
	}

	/**
	 * �w�蕶���񂪊܂܂�Ă��邩����
	 *
	 * @param const TString &szValue	�Ώە�����
	 * @param const TString &szAt		���蕶����
	 * @return		true	: �܂܂�Ă���
	 *				false	: �܂܂�Ă��Ȃ�
	 */
	static bool contains(const TString &szValue, const TString &szAt) {

		if (ATStringUtl::isEmpty(szValue) ||
			ATStringUtl::isEmpty(szAt)) {
			return false;
		}
		return szValue.find(szAt, 0) != szValue.npos;
	}

	/**
	 * �w�肳�ꂽ�f���~�^�ŕ�����𕪊�����
	 *
	 * @param const TString &szValue				������
	 * @param const TString &szDelimiter			�f���~�^
	 * @return ����������
	 */
	static std::list<TString> split(const TString &szValue, const TString &szDelimiter) {

		std::list<TString> splitList;
		if (!ATStringUtl::contains(szValue, szDelimiter)) {
			/* �f���~�^���܂܂�Ă��Ȃ��ꍇ�͋��Ԃ�	*/
			return splitList;
		}

		TString szBuff = szValue;
		unsigned int uiPos = 0;
		while ((uiPos = szBuff.find(szDelimiter, 0)) != szBuff.npos) {

			/* �f���~�^�܂ł̕������؂���	*/
			TString szBefore = szBuff.substr(0, uiPos);
			splitList.push_back(szBefore);

			szBuff = szBuff.substr(uiPos + szDelimiter.length());
		}
		if (!ATStringUtl::isEmpty(szBuff)) {
			splitList.push_back(szBuff);
		}
		return splitList;
	}

	/**
	 * �����񂩂����̕�������폜
	 *
	 * @param const TString &szSrc		������
	 * @param const TString &szDest		�폜������
	 * @return							�폜���ꂽ������
	 */
	static TString erase(const TString &szSrc, const TString &szDest) {

		TString szBuff = szSrc;
		unsigned int uiPos = szBuff.find(szDest, 0);
		if(uiPos == szBuff.npos){
			/* �폜�����񂪑��݂��Ȃ��ꍇ���̕������Ԃ�		*/
			return szBuff;
		}

		/* ���������̑O���A��		*/
		TString szBefore = szBuff.substr(0, uiPos);
		TString szAfter = szBuff.substr(uiPos + szDest.length());
		TString szRet = szBefore + szAfter;
		return szRet;
	};

	/**
	 * ���C�h�������}���`�o�C�g�����ϊ�
	 *
	 * @param const wchar_t *pSrc		�ϊ������C�h������
	 * @param char *pDest				�ϊ���}���`�o�C�g������
	 * @param const size_t iSize		�ϊ���̊m�ۗ̈�T�C�Y
	 * @return int
	 */
	static size_t wide2Multi(const wchar_t *pSrc, char *pDest, const size_t iSize)
	{
		if(pSrc == NULL || pDest == NULL){
			return AT_ERR_ARGUMENTS;
		}

		/* �ϊ��ɕK�v�ȃo�C�g�����擾		*/
		size_t uiSize = wcstombs(NULL, pSrc, iSize);
		if(uiSize == (size_t)-1){
			return AT_ERR_CONVEXCEPTION;
		}

		/* �T�C�Y�m�ۂ̐������`�F�b�N		*/
		if(iSize < uiSize){
			return AT_ERR_ARGUMENTS;
		}

		uiSize = wcstombs(pDest, pSrc, uiSize);
		if(uiSize == (size_t)-1){
			return AT_ERR_CONVEXCEPTION;
		}
		return uiSize;
	};

	/**
	 * �}���`�o�C�g���������C�h�����ϊ�
	 *
	 * @param const char_t *pSrc		�ϊ����}���`�o�C�g������
	 * @param wchar_t *pDest			�ϊ��惏�C�h������
	 * @param const size_t iSize		�ϊ���̊m�ۗ̈�T�C�Y
	 * @return int
	 */
	static int multi2Wide(const char *pSrc, wchar_t *pDest, const size_t iSize)
	{
		if(pSrc == NULL || pDest == NULL){
			return AT_ERR_ARGUMENTS;
		}

		/* �ϊ��ɕK�v�ȃT�C�Y���擾			*/
		size_t uiSize = mbstowcs(NULL, pSrc, iSize);
		if(uiSize ==(size_t)-1){
			return AT_ERR_CONVEXCEPTION;
		}

		/* �T�C�Y�m�ۂ̐������`�F�b�N		*/
		if(iSize < uiSize){
			return AT_ERR_ARGUMENTS;
		}

		// �ϊ�
		uiSize = mbstowcs(pDest, pSrc, uiSize);
		if(uiSize == (size_t)-1){
			return AT_ERR_CONVEXCEPTION;
		}
		return AT_OK;
	};

private:
	ATStringUtl();
};
#endif // __ATLIBSTRINGUTL_H__3B42A968_727A_46F7_8528_2E33B66B9152