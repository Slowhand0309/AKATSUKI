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
	unsigned int ml_nHeight; ///< �E�B���h�E��
	unsigned int ml_nWidth;	///< �E�B���h�E��
	unsigned int ml_nDispHeight; ///< �f�B�X�v���C��
	unsigned int ml_nDispWidth; ///< �f�B�X�v���C��
	TString	ml_szWindowTitle; ///< �E�B���h�E�^�C�g��
	bool ml_bWindowMode; ///< �E�B���h�E���[�h����

};
#endif // __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
