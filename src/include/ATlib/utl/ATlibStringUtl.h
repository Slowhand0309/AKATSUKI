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
	static bool isEmpty(const TString &szValue);

	/**
	 * Check for not empty
	 *
	 * @param const TString &szValue check value
	 * @return    true  :  not empty
	 *            false :  empty
	 */
	static bool isNotEmpty(const TString &szValue);

	/**
	 * check for digit
	 *
	 * @param const TString &szValue check value
	 * @return    true  :  digit
	 *            false :  not digit
	 */
	static bool isDigit(const TString &szValue);

	/**
	 * check for digit
	 *
	 * @param const cahr at     check value
	 * @return     true   : digit
	 *             false  : not digit
	 */
	static bool isDigit(const char at);

	/**
	 * check for contains string
	 *
	 * @param const TString &szValue  check value
	 * @param const TString &szAt     search value
	 * @return    true  :  contains
	 *            false :  not contains
	 */
	static bool contains(const TString &szValue, const TString &szAt);

	/**
	 * split string
	 *
	 * @param const TString &szValue string
	 * @param const TString &szDelimiter split value
	 * @return string list
	 */
	static std::list<TString> split(const TString &szValue, const TString &szDelimiter);

	/**
	 * erase string to szDest
	 *
	 * @param const TString &szSrc    string
	 * @param const TString &szDest   erase value
	 * @return  erase value
	 */
	static TString erase(const TString &szSrc, const TString &szDest);

	/**
	 * wide to multi string
	 *
	 * @param const wchar_t *pSrc  wide string
	 * @param char *pDest  multi byte string
	 * @param const size_t iSize  string size
	 * @return int
	 */
	static size_t wide2Multi(const wchar_t *pSrc, char *pDest, const size_t iSize);

	/**
	 * multi to wide string
	 *
	 * @param const char_t *pSrc  multi byte string
	 * @param wchar_t *pDest  wide string
	 * @param const size_t iSize  string size
	 * @return int
	 */
	static int multi2Wide(const char *pSrc, wchar_t *pDest, const size_t iSize);

private:
	ATStringUtl();
};
#endif // __ATLIBSTRINGUTL_H__3B42A968_727A_46F7_8528_2E33B66B9152
