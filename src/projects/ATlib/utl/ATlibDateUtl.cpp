#include "ATlib/utl/ATlibDateUtl.h"

/**
 * Get current date time(Y/m/d H:M:S).
 *
 * @return  current date time string
 */
TString ATDateUtl::getCurrentDate() {
  return getCurrentDate(DEFAULT_DATE_FORMAT);
}

/**
 * Get current date time(Y/m/d H:M:S).
 *
 * @param	szFormat date time format
 *
 * @return  current date time string
 */
TString ATDateUtl::getCurrentDate(TString szFormat) {

  time_t		lTime;
  struct tm	*tagNow;
  TCHAR		szTime[_MAX_PATH] = {0};

  time(&lTime);
  tagNow = localtime(&lTime);

  if (_tcsftime(szTime, _MAX_PATH, szFormat.c_str(), tagNow) == 0) {
    return TString();
  }
  return TString(szTime);
}

#ifdef PLATFORM_WINDOWS
/* declaration for windows					*/

/**
 * Get current date time use SYSTEMTIME
 *
 * @param	SYSTEMTIME stSysTime system time struct
 * @param	const TString &szFormat date time format
 * @return	TString date time string
 */
TString ATDateUtl::getFormatString(SYSTEMTIME stSysTime, const TString &szFormat) {

	if (ATStringUtl::isEmpty(szFormat)) {
		return AT_EMPTY_STR;
	}

	TCHAR		szValue[_MAX_PATH] = {0};
	_stprintf(szValue, szFormat.c_str(),
				stSysTime.wYear,   stSysTime.wMonth,
				stSysTime.wDay,    stSysTime.wHour,
				stSysTime.wMinute, stSysTime.wSecond);

	return TString(szValue);
}

#endif // PLATFORM_WINDOWS

/**
 * Constructor
 */
ATDateUtl::ATDateUtl() {

}
