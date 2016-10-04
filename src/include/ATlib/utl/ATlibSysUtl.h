#ifndef __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B
#define __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B

#include "ATlib/com/ATlibCommon.h"
#include "ATlib/utl/ATlibStringUtl.h"

/**
 * System utility class<br>
 * <b>ATlibSysUtl.h</b>
 *
 * @author slowhand0309
 */
class ATSysUtl
{
public:

	/**
	 * Get module name.
	 *
	 * @return TString moduel name
	 */
	static TString getModuleName();

	/**
	 * Get current path.
	 *
	 * @return TString path
	 */
	static TString getCurrentPath();

	/**
	 * Get file extension.
	 *
	 * @param const TString &szPath  file path
	 * @return TString file extension
	 */
	static TString getExtension(const TString &szPath);

	/**
	 * check path.
	 *
	 * @param const TString &szPath path for check
	 * @return true  : valid
	 *         false : unvalid
	 */
	static bool hasPath(const TString &szPath);

private:
	ATSysUtl();
};
#endif // __ATLIBSYSUTL_H__A8FC7AB2_A5F2_48BD_B274_02ADC28C767B
