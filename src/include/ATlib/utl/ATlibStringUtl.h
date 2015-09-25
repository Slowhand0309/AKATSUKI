#ifndef __ATLIBSTRINGUTL_H__3B42A968_727A_46F7_8528_2E33B66B9152
#define __ATLIBSTRINGUTL_H__3B42A968_727A_46F7_8528_2E33B66B9152

#include "ATlib/com/ATlibCommon.h"

/**
 * 文字ユーティリティクラス<br>
 * <b>ATlibStringUtl.h</b>
 *
 * @author slowhand0309
 */
class ATStringUtl
{
public:

	/**
	 * 空判定
	 *
	 * @param const TString &szValue 判定文字列
	 * @return		true	: 空
	 *				false	: 空でない
	 */
	static bool isEmpty(const TString &szValue) {
		if (&szValue == NULL) {
			return true;
		}
		return szValue.empty();
	};

	/**
	 * Not空判定
	 *
	 * @param const TString &szValue 判定文字列
	 * @return		true	: 空でない
	 *				false	: 空
	 */
	static bool isNotEmpty(const TString &szValue) {
		return !ATStringUtl::isEmpty(szValue);
	}

	/**
	 * 文字列の数値チェック
	 *
	 * @param const TString &szValue	判定文字列
	 * @return		true	: 数値
	 *				false	: 数値でない
	 */
	static bool isDigit(const TString &szValue) {

		if (ATStringUtl::isEmpty(szValue)) {
			return false;
		}

		char szBuff[_MAX_PATH] = {0};
		const TCHAR *szTemp = szValue.c_str();
		int nSize = szValue.length();

#ifdef _UNICODE
		/* マルチバイト文字へ変換		*/
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
	 * 数値チェック
	 *
	 * @param const cahr at			判定文字
	 * @return						true	: 数値
	 *								false	: 数値以外
	 */
	static bool isDigit(const char at) {

		if (isdigit(at)) {
			return true;
		}
		return false;
	}

	/**
	 * 指定文字列が含まれているか判定
	 *
	 * @param const TString &szValue	対象文字列
	 * @param const TString &szAt		判定文字列
	 * @return		true	: 含まれている
	 *				false	: 含まれていない
	 */
	static bool contains(const TString &szValue, const TString &szAt) {

		if (ATStringUtl::isEmpty(szValue) ||
			ATStringUtl::isEmpty(szAt)) {
			return false;
		}
		return szValue.find(szAt, 0) != szValue.npos;
	}

	/**
	 * 指定されたデリミタで文字列を分割する
	 *
	 * @param const TString &szValue				文字列
	 * @param const TString &szDelimiter			デリミタ
	 * @return 分割文字列
	 */
	static std::list<TString> split(const TString &szValue, const TString &szDelimiter) {

		std::list<TString> splitList;
		if (!ATStringUtl::contains(szValue, szDelimiter)) {
			/* デリミタが含まれていない場合は空を返す	*/
			return splitList;
		}

		TString szBuff = szValue;
		unsigned int uiPos = 0;
		while ((uiPos = szBuff.find(szDelimiter, 0)) != szBuff.npos) {

			/* デリミタまでの文字列を切り取る	*/
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
	 * 文字列から特定の文字列を削除
	 *
	 * @param const TString &szSrc		文字列
	 * @param const TString &szDest		削除文字列
	 * @return							削除された文字列
	 */
	static TString erase(const TString &szSrc, const TString &szDest) {

		TString szBuff = szSrc;
		unsigned int uiPos = szBuff.find(szDest, 0);
		if(uiPos == szBuff.npos){
			/* 削除文字列が存在しない場合元の文字列を返す		*/
			return szBuff;
		}

		/* 検索文字の前後を連結		*/
		TString szBefore = szBuff.substr(0, uiPos);
		TString szAfter = szBuff.substr(uiPos + szDest.length());
		TString szRet = szBefore + szAfter;
		return szRet;
	};

	/**
	 * ワイド文字→マルチバイト文時変換
	 *
	 * @param const wchar_t *pSrc		変換元ワイド文字列
	 * @param char *pDest				変換先マルチバイト文字列
	 * @param const size_t iSize		変換先の確保領域サイズ
	 * @return int
	 */
	static size_t wide2Multi(const wchar_t *pSrc, char *pDest, const size_t iSize)
	{
		if(pSrc == NULL || pDest == NULL){
			return AT_ERR_ARGUMENTS;
		}

		/* 変換に必要なバイト数を取得		*/
		size_t uiSize = wcstombs(NULL, pSrc, iSize);
		if(uiSize == (size_t)-1){
			return AT_ERR_CONVEXCEPTION;
		}

		/* サイズ確保の正当性チェック		*/
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
	 * マルチバイト文字→ワイド文時変換
	 *
	 * @param const char_t *pSrc		変換元マルチバイト文字列
	 * @param wchar_t *pDest			変換先ワイド文字列
	 * @param const size_t iSize		変換先の確保領域サイズ
	 * @return int
	 */
	static int multi2Wide(const char *pSrc, wchar_t *pDest, const size_t iSize)
	{
		if(pSrc == NULL || pDest == NULL){
			return AT_ERR_ARGUMENTS;
		}

		/* 変換に必要なサイズを取得			*/
		size_t uiSize = mbstowcs(NULL, pSrc, iSize);
		if(uiSize ==(size_t)-1){
			return AT_ERR_CONVEXCEPTION;
		}

		/* サイズ確保の正当性チェック		*/
		if(iSize < uiSize){
			return AT_ERR_ARGUMENTS;
		}

		// 変換
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