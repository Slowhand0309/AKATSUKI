#ifndef __ATUTILLISTCTRL_H__1850A507_1777_4EA9_81AA_1CBE29A9F2A6
#define __ATUTILLISTCTRL_H__1850A507_1777_4EA9_81AA_1CBE29A9F2A6
#include "ATlib/com/ATlibCommon.h"

/**
 * MFCでのCListCtrl拡張クラス
 * ATutlListCtrl.h
 *
 * @author	slowhand0309
 */
class ATListCtrl : public CListCtrl
{
public:

	/**
	 * コンストラクタ
	 */
	ATListCtrl();

	/**
	 * デストラクタ
	 */
	virtual ~ATListCtrl();

	/**
	 * ヘッダ設定
	 *
	 * @param	int	nIndex				インデックス
	 * @param	CString	&szItemName		カラム名称
	 * @param	int nSize				カラムサイズ
	 */
	void insertHeadItem(int nIndex, CString &szItemName, int nSize);

	/**
	 * リストへ一行追加
	 *
	 * @param	int nIndex				インデックス
	 * @param	int nSubIndex			サブインデックス
	 * @param	CString &szItem			設定データ
	 */
	void setListData(int nIndex, int nSubIndex, CString &szItem);

	/**
	 * グリッドラインスタイルに変更
	 */
	void setGridLineStyle();

	/**
	 * チェックボックスを付加します
	 */
	void setCheckBoxStyle();

	/**
	 * 現在チェックされているカラムデータリストを取得
	 *
	 * @param std::list<CString> &oCheckedData		データリスト
	 * @return int
	 */
	int getCheckColumnData(std::list<CString> &oCheckedData);

	/**
	 * 現在チェックされているインデックスリストを取得
	 *
	 * @param std::list<int> &oCheckedIndex			インデックスリスト
	 * @return int
	 */
	int getCheckColumnIndex(std::list<int> &oCheckedIndex);

	/**
	 * 現在選択されている行番号リストを取得
	 *
	 * @param std::list<int> &oIndexList			行番号リスト
	 */
	void getSelectedIndex(std::list<int> &oIndexList);

	/**
	 * ソート
	 */
	void sort(int nSubIndex);

	static int CALLBACK CompareFunc(LPARAM param1, LPARAM param2, LPARAM param3);

private:

	bool		ml_bCheckStyle;
};
#endif // __ATUTILLISTCTRL_H__1850A507_1777_4EA9_81AA_1CBE29A9F2A6