#ifndef __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
#define __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10
#include "ATlib/com/ATlibCommon.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * <b>ウィンドウ情報クラス</b><br>
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
 *     <td>新規作成</td>
 *   </tr>
 * </table>
 */
class ATWindowInfo
{
public:

	/**
	 * コンストラクタ
	 */
	ATWindowInfo();

	/**
	 * デストラクタ
	 */
	virtual ~ATWindowInfo();

	/**
	 * クライアント幅取得
	 *
	 * @return クライアント幅
	 */
	unsigned int getHeight();

	/**
	 * クライアント幅の設定
	 *
	 * @param unsigned int nHeight	クライアント幅
	 */
	void setHeight(unsigned int nHeight);

	/**
	 * クライアント高取得
	 *
	 * @return クライアント高
	 */
	unsigned int getWidth();

	/**
	 * クライアント高の設定
	 *
	 * @param クライアント高
	 */
	void setWidth(unsigned int nWidth);

private:
	unsigned int			ml_nHeight;			///< ウィンドウ高
	unsigned int			ml_nWidth;			///< ウィンドウ幅
	unsigned int			ml_nDispHeight;		///< ディスプレイ高
	unsigned int			ml_nDispWidth;		///< ディスプレイ幅
	TString					ml_szWindowTitle;	///< ウィンドウタイトル
	bool					ml_bWindowMode;		///< ウィンドウモード判定

};
#endif // __ATWINDOWINFO_H__B9F67094_62AF_4F89_87F5_CCBB3134FE10