#ifndef __ATUTILLISTCTRL_H__1850A507_1777_4EA9_81AA_1CBE29A9F2A6
#define __ATUTILLISTCTRL_H__1850A507_1777_4EA9_81AA_1CBE29A9F2A6
#include "ATlib/com/ATlibCommon.h"

/**
 * MFC�ł�CListCtrl�g���N���X
 * ATutlListCtrl.h
 *
 * @author	slowhand0309
 */
class ATListCtrl : public CListCtrl
{
public:

	/**
	 * �R���X�g���N�^
	 */
	ATListCtrl();

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATListCtrl();

	/**
	 * �w�b�_�ݒ�
	 *
	 * @param	int	nIndex				�C���f�b�N�X
	 * @param	CString	&szItemName		�J��������
	 * @param	int nSize				�J�����T�C�Y
	 */
	void insertHeadItem(int nIndex, CString &szItemName, int nSize);

	/**
	 * ���X�g�ֈ�s�ǉ�
	 *
	 * @param	int nIndex				�C���f�b�N�X
	 * @param	int nSubIndex			�T�u�C���f�b�N�X
	 * @param	CString &szItem			�ݒ�f�[�^
	 */
	void setListData(int nIndex, int nSubIndex, CString &szItem);

	/**
	 * �O���b�h���C���X�^�C���ɕύX
	 */
	void setGridLineStyle();

	/**
	 * �`�F�b�N�{�b�N�X��t�����܂�
	 */
	void setCheckBoxStyle();

	/**
	 * ���݃`�F�b�N����Ă���J�����f�[�^���X�g���擾
	 *
	 * @param std::list<CString> &oCheckedData		�f�[�^���X�g
	 * @return int
	 */
	int getCheckColumnData(std::list<CString> &oCheckedData);

	/**
	 * ���݃`�F�b�N����Ă���C���f�b�N�X���X�g���擾
	 *
	 * @param std::list<int> &oCheckedIndex			�C���f�b�N�X���X�g
	 * @return int
	 */
	int getCheckColumnIndex(std::list<int> &oCheckedIndex);

	/**
	 * ���ݑI������Ă���s�ԍ����X�g���擾
	 *
	 * @param std::list<int> &oIndexList			�s�ԍ����X�g
	 */
	void getSelectedIndex(std::list<int> &oIndexList);

	/**
	 * �\�[�g
	 */
	void sort(int nSubIndex);

	static int CALLBACK CompareFunc(LPARAM param1, LPARAM param2, LPARAM param3);

private:

	bool		ml_bCheckStyle;
};
#endif // __ATUTILLISTCTRL_H__1850A507_1777_4EA9_81AA_1CBE29A9F2A6