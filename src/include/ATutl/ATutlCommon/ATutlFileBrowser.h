#ifndef __ATUTLFILEBROWSER_H__ECBB0414_D3CB_446F_A3AD_5677BA1F12BC
#define __ATUTLFILEBROWSER_H__ECBB0414_D3CB_446F_A3AD_5677BA1F12BC
#include "ATlib/com/ATlibCommon.h"

struct FileProperty
{
	TString		m_szFileName;	// ファイル名称
	TString		m_szAttribute;	// 属性
	TString		m_szCreateDate;	// 作成日時
	TString		m_szUpdateDate;	// 更新日時
};

class ATFileBrowser
{
public:

	/**
	 * コンストラクタ
	 */
	ATFileBrowser();

	/**
	 * デストラクタ
	 */
	virtual ~ATFileBrowser();

	/**
	 * フォルダ参照
	 *
	 * @return	参照先フォルダーパス
	 *			キャンセル時、エラー時は空文字
	 */
	TString browseFolder();

	/**
	 * 指定ディレクトリのファイル一覧取得
	 *
	 * @param	const TString &szDir				指定ディレクトリ
	 * @param	const TString &szExt				拡張子
	 * @param	std::list<FileProperty> &oFileList	取得ファイルリスト
	 * @return	int
	 */
	int getFileList(const TString &szDir, 
		const TString &szExt, std::list<FileProperty> &oFileList);

	/**
	 * ファイルの属性文字列を取得
	 *
	 * @param	const DWORD dwAttribute				属性
	 * @return	TString								属性文字列
	 */
	TString getFileArrtibuteStr(const DWORD dwAttribute);

	/**
	 * ファイル日時を文字列に変換
	 *
	 * @param	const FILETIME stFileTime			ファイル日時
	 * @return	TString								文字列
	 */
	TString getFileTimeStr(const FILETIME stFileTime);

private:
	
};
#endif // __ATUTLFILEBROWSER_H__ECBB0414_D3CB_446F_A3AD_5677BA1F12BC