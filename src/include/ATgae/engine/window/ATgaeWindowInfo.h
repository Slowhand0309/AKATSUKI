#ifndef __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
#define __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
#include "ATlib/com/ATlibCommon.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * <b>�E�B���h�E���N���X</b><br>
 * @author j-fujisaki
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
 *     <td>�V�K�쐬</td>
 *   </tr>
 * </table>
 */
class ATWindowInfo
{
public:

	/**
	 * �R���X�g���N�^
	 */
	ATWindowInfo();

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATWindowInfo();

	/**
	 * �N���C�A���g���擾
	 *
	 * @return �N���C�A���g��
	 */
	unsigned int getHeight();

	/**
	 * �N���C�A���g���̐ݒ�
	 *
	 * @param unsigned int nHeight	�N���C�A���g��
	 */
	void setHeight(unsigned int nHeight);

	/**
	 * �N���C�A���g���擾
	 *
	 * @return �N���C�A���g��
	 */
	unsigned int getWidth();

	/**
	 * �N���C�A���g���̐ݒ�
	 *
	 * @param �N���C�A���g��
	 */
	void setWidth(unsigned int nWidth);

private:
	unsigned int			ml_nHeight;			///< �E�B���h�E��
	unsigned int			ml_nWidth;			///< �E�B���h�E��
	unsigned int			ml_nDispHeight;		///< �f�B�X�v���C��
	unsigned int			ml_nDispWidth;		///< �f�B�X�v���C��
	TString					ml_szWindowTitle;	///< �E�B���h�E�^�C�g��
	bool					ml_bWindowMode;		///< �E�B���h�E���[�h����

};
#endif // __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10