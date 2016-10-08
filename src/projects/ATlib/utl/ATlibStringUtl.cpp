#include "ATlib/utl/ATlibStringUtl.h"

/**
 * Check for empty
 *
 * @param szValue check value
 * @return    true  :  empty
 *            false :  not empty
 */
bool ATStringUtl::isEmpty(const TString &szValue) {
  return szValue.empty();
};

/**
 * Check for not empty
 *
 * @param szValue check value
 * @return    true  :  not empty
 *            false :  empty
 */
bool ATStringUtl::isNotEmpty(const TString &szValue) {
  return !ATStringUtl::isEmpty(szValue);
}

/**
 * check for digit
 *
 * @param szValue check value
 * @return    true  :  digit
 *            false :  not digit
 */
bool ATStringUtl::isDigit(const TString &szValue) {

  if (ATStringUtl::isEmpty(szValue)) {
    return false;
  }

  char szBuff[_MAX_PATH] = {0};
  const TCHAR *szTemp = szValue.c_str();
  int nSize = (int)szValue.length();
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
 * @param at     check value
 * @return     true   : digit
 *             false  : not digit
 */
bool ATStringUtl::isDigit(const char at) {

  if (isdigit(at)) {
    return true;
  }
  return false;
}

/**
 * check for contains string
 *
 * @param szValue  check value
 * @param szAt     search value
 * @return    true  :  contains
 *            false :  not contains
 */
bool ATStringUtl::contains(const TString &szValue, const TString &szAt) {

  if (ATStringUtl::isEmpty(szValue) ||
    ATStringUtl::isEmpty(szAt)) {
    return false;
  }
  return szValue.find(szAt, 0) != szValue.npos;
}

/**
 * split string
 *
 * @param szValue string
 * @param szDelimiter split value
 * @return string list
 */
std::list<TString> ATStringUtl::split(const TString &szValue, const TString &szDelimiter) {

  std::list<TString> splitList;
  if (!ATStringUtl::contains(szValue, szDelimiter)) {
    return splitList;
  }

  TString szBuff = szValue;
  unsigned int uiPos = 0;
  while ((uiPos = (unsigned int)szBuff.find(szDelimiter, 0)) != (unsigned int)szBuff.npos) {
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
 * @param szSrc    string
 * @param szDest   erase value
 * @return  erase value
 */
TString ATStringUtl::erase(const TString &szSrc, const TString &szDest) {

  TString szBuff = szSrc;
  unsigned int uiPos = (unsigned int)szBuff.find(szDest, 0);
  if(uiPos == (unsigned int)szBuff.npos){
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
 * @param pSrc  wide string
 * @param pDest  multi byte string
 * @param iSize  string size
 * @return int
 */
size_t ATStringUtl::wide2Multi(const wchar_t *pSrc, char *pDest, const size_t iSize)
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
 * @param pSrc  multi byte string
 * @param pDest  wide string
 * @param iSize  string size
 * @return int
 */
int ATStringUtl::multi2Wide(const char *pSrc, wchar_t *pDest, const size_t iSize)
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
}

/**
 * Convert char to TString.
 *
 * @param pSrc multibyte
 * @return TString
 */
TString ATStringUtl::toTString(const char *pSrc)
{
  TString result = _T("");
#ifdef _UNICODE
  wchar_t pDest[BUFF_SIZE] = {0};
  ATStringUtl::multi2Wide(pSrc, pDest, BUFF_SIZE);
  result = TString(pDest);
#else
  result = TString(pSrc);
#endif // _UNICODE
  return result;
}

/**
 * Convert wchar_t to TString.
 *
 * @param pSrc wide
 * @return TString
 */
TString ATStringUtl::toTString(const wchar_t *pSrc)
{
  TString result = _T("");
#ifdef _UNICODE
  result = TString(pSrc);
#else
  char pDest[BUFF_SIZE] = {0};
  ATStringUtl::wide2Multi(pSrc, pDest, BUFF_SIZE);
  result = TString(pDest);
#endif // _UNICODE
  return result;
}

ATStringUtl::ATStringUtl() {
}
