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
	 * Constructor
	 */
	ATWindowInfo();

	/**
	 * Destructor
	 */
	virtual ~ATWindowInfo();

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
	void setHeight(unsigned int nHeight);

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
	void setWidth(unsigned int nWidth);

private:
	unsigned int ml_nHeight; ///< ウィンドウ高
	unsigned int ml_nWidth;	///< ウィンドウ幅
	unsigned int ml_nDispHeight; ///< ディスプレイ高
	unsigned int ml_nDispWidth; ///< ディスプレイ幅
	TString	ml_szWindowTitle; ///< ウィンドウタイトル
	bool ml_bWindowMode; ///< ウィンドウモード判定

};
#endif // __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
