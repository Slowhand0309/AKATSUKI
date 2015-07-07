#include "stdafx.h"
#include "ATutl/ATutlCommon/ATutlListCtrl.h"

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATListCtrl::ATListCtrl()
	: ml_bCheckStyle(false)
{
}

//********************************************************************************************
/**
 * �f�X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATListCtrl::~ATListCtrl()
{
}

//********************************************************************************************
/**
 * �w�b�_�ݒ�
 *
 * @param	int	nIndex				�C���f�b�N�X
 * @param	CString	&szItemName		�J��������
 * @param	int nSize				�J�����T�C�Y
 */
//********************************************************************************************
void ATListCtrl::insertHeadItem(
	int				nIndex,
	CString			&szItemName,
	int				nSize)
{
	LVCOLUMN    lvc;

	/* �w�b�_���\���̂ɐݒ�		*/
	lvc.mask =  LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.iSubItem = nIndex;
	lvc.pszText = szItemName.GetBuffer();
	lvc.cx = nSize;

	this->InsertColumn(nIndex, &lvc);
}

//********************************************************************************************
/**
 * ���X�g�ֈ�s�ǉ�
 *
 * @param	int nIndex				�C���f�b�N�X
 * @param	int nSubIndex			�T�u�C���f�b�N�X
 * @param	CString &szItem			�ݒ�f�[�^
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
 * �O���b�h���C���X�^�C���ɕύX
 *
 * @param			�Ȃ�.
 */
//********************************************************************************************
void ATListCtrl::setGridLineStyle()
{
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_FULLROWSELECT | 
					  LVS_EX_GRIDLINES  | LVS_EX_HEADERDRAGDROP);
}

//********************************************************************************************
/**
 * �`�F�b�N�{�b�N�X��t�����܂�
 *
 * @param			�Ȃ�.
 */
//********************************************************************************************
void ATListCtrl::setCheckBoxStyle()
{
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_CHECKBOXES );
	ml_bCheckStyle = true;
}

//********************************************************************************************
/**
 * ���݃`�F�b�N����Ă���J�����f�[�^���X�g���擾
 *
 * @param std::list<CString> &oCheckedData		�f�[�^���X�g
 *
 * @return			AT_OK					: ����
 *					AT_ERR_CONTRADICTION	: ���������G���[
 */
//********************************************************************************************
int ATListCtrl::getCheckColumnData(std::list<CString> &oCheckedData)
{
	if(!ml_bCheckStyle){
		return AT_ERR_CONTRADICTION;
	}

	/* ���X�g��̑��������擾		*/
	const int iIndexs = this->GetItemCount();
	for(int i = 0; i < iIndexs; i++){

		/* �`�F�b�N����		*/
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
 * ���݃`�F�b�N����Ă���C���f�b�N�X���X�g���擾
 *
 * @param std::list<int> &oCheckedIndex		�C���f�b�N�X���X�g
 *
 * @return			AT_OK					: ����
 *					AT_ERR_CONTRADICTION	: ���������G���[
 */
//********************************************************************************************
int ATListCtrl::getCheckColumnIndex(std::list<int> &oCheckedIndex)
{
	if(!ml_bCheckStyle){
		return AT_ERR_CONTRADICTION;
	}

	/* ���X�g��̑��������擾		*/
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
 * ���ݑI������Ă���s�ԍ����X�g���擾
 *
 * @param std::list<int> &oIndexList			�s�ԍ����X�g
 */
//********************************************************************************************
void ATListCtrl::getSelectedIndex(std::list<int> &oIndexList)
{
	int iIndex = 0;

	while(1){
		/* �S�Ă̑I���C���f�b�N�X���擾����		*/
		iIndex = this->GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if(iIndex != -1){
			oIndexList.push_back(iIndex);
		} else {
			break;
		}
	}

}