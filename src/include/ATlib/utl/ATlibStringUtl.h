#ifndef __ATLIBSTRINGUTL_H__3B42A968_727A_46F7_8528_2E33B66B9152
#define __ATLIBSTRINGUTL_H__3B42A968_727A_46F7_8528_2E33B66B9152

#include "ATlib/com/ATlibCommon.h"

/**
 * String utility class<br>
 * <b>ATlibStringUtl.h</b>
 *
 * @author slowhand0309
 */
class ATStringUtl
{
public:

	/**
	 * Check for empty
	 *
	 * @param const TString &szValue check value
	 * @return    true  :  empty
	 *            false :  not empty
	 */
	static bool isEmpty(const TString &szValue) {
		if (&szValue == NULL) {
			return true;
		}
		return szValue.empty();
	};

	/**
	 * Check for not empty
	 *
	 * @param const TString &szValue check value
	 * @return    true  :  not empty
	 *            false :  empty
	 */
	static bool isNotEmpty(const TString &szValue) {
		return !ATStringUtl::isEmpty(szValue);
	}

	/**
	 * check for digit
	 *
	 * @param const TString &szValue check value
	 * @return    true  :  digit
	 *            false :  not digit
	 */
	static bool isDigit(const TString &szValue) {

		if (ATStringUtl::isEmpty(szValue)) {
			return false;
		}

		char szBuff[_MAX_PATH] = {0};
		const TCHAR *szTemp = szValue.c_str();
		int nSize = szValue.length();
#ifdef _UNICODE
		/* convert unicode */
		nSize = ATStringUtl::wide2Multi(szTemp, szBuff, nSize);
#else
    strcpy(szBuff, szTemp);
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
	 * check for digit
	 *
	 * @param const cahr at     check value
	 * @return     true   : digit
	 *             false  : not digit
	 */
	static bool isDigit(const char at) {

		if (isdigit(at)) {
			return true;
		}
		return false;
	}

	/**
	 * check for contains string
	 *
	 * @param const TString &szValue  check value
	 * @param const TString &szAt     search value
	 * @return    true  :  contains
	 *            false :  not contains
	 */
	static bool contains(const TString &szValue, const TString &szAt) {

		if (ATStringUtl::isEmpty(szValue) ||
			ATStringUtl::isEmpty(szAt)) {
			return false;
		}
		return szValue.find(szAt, 0) != szValue.npos;
	}

	/**
	 * split string
	 *
	 * @param const TString &szValue string
	 * @param const TString &szDelimiter split value
	 * @return string list
	 */
	static std::list<TString> split(const TString &szValue, const TString &szDelimiter) {

		std::list<TString> splitList;
		if (!ATStringUtl::contains(szValue, szDelimiter)) {
			return splitList;
		}

		TString szBuff = szValue;
		unsigned int uiPos = 0;
		while ((uiPos = szBuff.find(szDelimiter, 0)) != (unsigned int)szBuff.npos) {
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
	 * erase string to szDest
	 *
	 * @param const TString &szSrc    string
	 * @param const TString &szDest   erase value
	 * @return  erase value
	 */
	static TString erase(const TString &szSrc, const TString &szDest) {

		TString szBuff = szSrc;
		unsigned int uiPos = szBuff.find(szDest, 0);
		if(uiPos == szBuff.npos){
			return szBuff;
		}

		TString szBefore = szBuff.substr(0, uiPos);
		TString szAfter = szBuff.substr(uiPos + szDest.length());
		TString szRet = szBefore + szAfter;
		return szRet;
	};

	/**
	 * wide to multi string
	 *
	 * @param const wchar_t *pSrc  wide string
	 * @param char *pDest  multi byte string
	 * @param const size_t iSize  string size
	 * @return int
	 */
	static size_t wide2Multi(const wchar_t *pSrc, char *pDest, const size_t iSize)
	{
		if(pSrc == NULL || pDest == NULL){
			return AT_ERR_ARGUMENTS;
		}

		size_t uiSize = wcstombs(NULL, pSrc, iSize);
		if(uiSize == (size_t)-1){
			return AT_ERR_CONVEXCEPTION;
		}

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
	 * multi to wide string
	 *
	 * @param const char_t *pSrc  multi byte string
	 * @param wchar_t *pDest  wide string
	 * @param const size_t iSize  string size
	 * @return int
	 */
	static int multi2Wide(const char *pSrc, wchar_t *pDest, const size_t iSize)
	{
		if(pSrc == NULL || pDest == NULL){
			return AT_ERR_ARGUMENTS;
		}

		size_t uiSize = mbstowcs(NULL, pSrc, iSize);
		if(uiSize ==(size_t)-1){
			return AT_ERR_CONVEXCEPTION;
		}

		if(iSize < uiSize){
			return AT_ERR_ARGUMENTS;
		}

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
