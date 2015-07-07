#include "stdafx.h"
#include "ATutl/ATutlCommon/ATutlListCtrl.h"

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATListCtrl::ATListCtrl()
	: ml_bCheckStyle(false)
{
}

//********************************************************************************************
/**
 * デストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATListCtrl::~ATListCtrl()
{
}

//********************************************************************************************
/**
 * ヘッダ設定
 *
 * @param	int	nIndex				インデックス
 * @param	CString	&szItemName		カラム名称
 * @param	int nSize				カラムサイズ
 */
//********************************************************************************************
void ATListCtrl::insertHeadItem(
	int				nIndex,
	CString			&szItemName,
	int				nSize)
{
	LVCOLUMN    lvc;

	/* ヘッダ情報構造体に設定		*/
	lvc.mask =  LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.iSubItem = nIndex;
	lvc.pszText = szItemName.GetBuffer();
	lvc.cx = nSize;

	this->InsertColumn(nIndex, &lvc);
}

//********************************************************************************************
/**
 * リストへ一行追加
 *
 * @param	int nIndex				インデックス
 * @param	int nSubIndex			サブインデックス
 * @param	CString &szItem			設定データ
 */
//********************************************************************************************
void ATListCtrl::setListData(
	int				nIndex,
	int				nSubIndex,
	CString			&szItem)
{
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = nIndex;
	lvi.iSubItem = nSubIndex;
	lvi.pszText = szItem.GetBuffer();

	if(nSubIndex == 0){
		this->InsertItem(&lvi);
	} else {
		this->SetItem(&lvi);
	}
}

//********************************************************************************************
/**
 * グリッドラインスタイルに変更
 *
 * @param			なし.
 */
//********************************************************************************************
void ATListCtrl::setGridLineStyle()
{
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_FULLROWSELECT | 
					  LVS_EX_GRIDLINES  | LVS_EX_HEADERDRAGDROP);
}

//********************************************************************************************
/**
 * チェックボックスを付加します
 *
 * @param			なし.
 */
//********************************************************************************************
void ATListCtrl::setCheckBoxStyle()
{
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_CHECKBOXES );
	ml_bCheckStyle = true;
}

//********************************************************************************************
/**
 * 現在チェックされているカラムデータリストを取得
 *
 * @param std::list<CString> &oCheckedData		データリスト
 *
 * @return			AT_OK					: 正常
 *					AT_ERR_CONTRADICTION	: 内部矛盾エラー
 */
//********************************************************************************************
int ATListCtrl::getCheckColumnData(std::list<CString> &oCheckedData)
{
	if(!ml_bCheckStyle){
		return AT_ERR_CONTRADICTION;
	}

	/* リスト上の総件数を取得		*/
	const int iIndexs = this->GetItemCount();
	for(int i = 0; i < iIndexs; i++){

		/* チェック判定		*/
		if(ListView_GetCheckState(this->m_hWnd, i) == TRUE){
			CString szBuff = _T("");
			szBuff = this->GetItemText(i, 0);
			oCheckedData.push_back(szBuff);
		}
	}
	return AT_OK;
}

//********************************************************************************************
/**
 * 現在チェックされているインデックスリストを取得
 *
 * @param std::list<int> &oCheckedIndex		インデックスリスト
 *
 * @return			AT_OK					: 正常
 *					AT_ERR_CONTRADICTION	: 内部矛盾エラー
 */
//********************************************************************************************
int ATListCtrl::getCheckColumnIndex(std::list<int> &oCheckedIndex)
{
	if(!ml_bCheckStyle){
		return AT_ERR_CONTRADICTION;
	}

	/* リスト上の総件数を取得		*/
	const int iIndexs = this->GetItemCount();
	for(int i = 0; i < iIndexs; i++){
		if(ListView_GetCheckState(this->m_hWnd, i) == TRUE){
			oCheckedIndex.push_back(i);
		}
	}
	return AT_OK;
}

//********************************************************************************************
/**
 * 現在選択されている行番号リストを取得
 *
 * @param std::list<int> &oIndexList			行番号リスト
 */
//********************************************************************************************
void ATListCtrl::getSelectedIndex(std::list<int> &oIndexList)
{
	int iIndex = 0;

	while(1){
		/* 全ての選択インデックスを取得する		*/
		iIndex = this->GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if(iIndex != -1){
			oIndexList.push_back(iIndex);
		} else {
			break;
		}
	}

}