#ifndef __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75
#define __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75

#include "ATlib/com/ATlibCommon.h"
#include "ATlib/utl/ATlibStringUtl.h"
#include <time.h>

#define DEFAULT_DATE_FORMAT  _T("%Y/%m/%d %H:%M:%S")

/**
 * Date time utility class<br>
 * <b>ATlibDateUtl.h</b>
 *
 * @author slowhand0309
 */
class ATDateUtl
{
public:

	/**
	 * Get current date time(Y/m/d H:M:S).
	 *
	 * @return  current date time string
	 */
	static TString getCurrentDate();

	/**
	 * Get current date time(Y/m/d H:M:S).
	 *
	 * @param		TString szFormat date time format
	 *
	 * @return  current date time string
	 */
	static TString getCurrentDate(TString szFormat);

#ifdef PLATFORM_WINDOWS
/* declaration for windows					*/

 /**
  * Get current date time use SYSTEMTIME
  *
  * @param	SYSTEMTIME stSysTime system time struct
  * @param	const TString &szFormat date time format
  * @return	TString date time string
  */
	static TString getFormatString(SYSTEMTIME stSysTime, const TString &szFormat);

#endif // PLATFORM_WINDOWS

private:
	/**
	 * Constructor
	 */
	ATDateUtl();
};
#endif // __ATLIBDATEUTL_H__94544885_160A_4FAA_889E_3460630A9C75
