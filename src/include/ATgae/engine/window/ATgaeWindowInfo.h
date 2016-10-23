#ifndef __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
#define __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
#include "ATlib/com/ATlibCommon.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * <b>Info for Window</b><br>
 * @author slowhand
 *
 * <table>
 *   <tr>
 *     <th>No.</th>
 *     <th>Data.</th>
 *     <th>ReleaseNote.</th>
 *   </tr>
 *   <tr>
 *     <td>1</td>
 *     <td>2015.04.13</td>
 *     <td>Create file</td>
 *   </tr>
 * </table>
 */
class ATWindowInfo
{
public:

	/**
	 * Constructor.
	 */
	ATWindowInfo();

	/**
	 * Destructor.
	 */
	virtual ~ATWindowInfo();

	/**
	 * operator= .
	 */
	ATWindowInfo &operator=(const ATWindowInfo &obj);

	/**
	 * Get height size for client window.
	 *
	 * @return size
	 */
	unsigned int getHeight();

	/**
	 * Set height size for client window.
	 *
	 * @param unsigned int nHeight size
	 */
	void setHeight(unsigned int height);

	/**
	 * Get width size for client window.
	 *
	 * @return size
	 */
	unsigned int getWidth();

	/**
	 * Set width size for client window.
	 *
	 * @param size
	 */
	void setWidth(unsigned int width);

	/**
	 * Get height size for display window.
	 *
	 * @return size
	 */
	unsigned int getDispHeight();

	/**
	 * Set height size for client window.
	 *
	 * @param size
	 */
	void setDispHeight(unsigned int dispHeight);

	/**
	 * Get width size for display window.
	 *
	 * @return size
	 */
	unsigned int getDispWidth();

	/**
	 * Set width size for client window.
	 *
	 * @param size
	 */
	void setDispWidth(unsigned int dispWidth);

	/**
	 * Get width title.
	 *
	 * @return title string
	 */
	TString getWindowTitle();

	/**
	 * Set width title.
	 *
	 * @param title string
	 */
	void setWindowTitle(const TString &windowTitle);

	/**
	 * Get width mode.
	 *
	 * @return true : window / false : fullscreen
	 */
	bool isWindowMode();

	/**
	 * Set width mode.
	 *
	 * @param true : window / false : fullscreen
	 */
	void setWindowMode(bool windowMode);

private:
	unsigned int ml_nHeight; ///< Client window height size.
	unsigned int ml_nWidth;	///< Clinet window width size.
	unsigned int ml_nDispHeight; ///< Display window height size.
	unsigned int ml_nDispWidth; ///< Display window width size.
	TString	ml_szWindowTitle; ///< Window title string.
	bool ml_bWindowMode; ///< Window or Fullscreen.

};
#endif // __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
