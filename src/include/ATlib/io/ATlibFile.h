#ifndef __ATLIBFILE_H__EECA9CB2_0CC6_474E_8668_296B9B4B730B
#define __ATLIBFILE_H__EECA9CB2_0CC6_474E_8668_296B9B4B730B

#include "ATlib/io/ATlibStream.h"

/**
 * ファイル操作クラス<br>
 * <b>ATlibFile.h</b>
 *
 * @author slowhand0309
 */
class ATFile : public ATStream
{
public:
	/**
	 * コンストラクタ
	 */
	ATFile();

	/**
	 * コンストラクタ
	 *
	 * @param	const TString &fileName		ファイル名称
	 * @param	const enum OpenMode eMode	モード
	 */
	ATFile(const TString &fileName, const enum OpenMode eMode);

	/**
	 * デストラクタ
	 */
	virtual ~ATFile();

	/**
	 * ファイルオープン処理
	 *
	 * @param	const TString &szName		ファイル名称
	 * @param	const enum OpenMode eMode	モード
	 *
	 * @return	AT_OK	: 正常
	 */
	virtual int open(const TString &szName, const enum OpenMode eMode);

	/**
	 * ファイルクローズ処理
	 */
	virtual void close();

	/**
	 * ファイル書込
	 *
	 * @param	LPCVOID pData				書込データ
	 * @param	size_t uiSize				書込サイズ
	 *
	 * @return	AT_OK	: 正常
	 */
	virtual int write(LPCVOID pData, size_t uiSize);

	/**
	 * ファイル書込
	 * <br>ファイル一行分文字列を書き込む
	 *
	 * @param	const TString &szData		書込文字列
	 * @param	...							可変長引数
	 *
	 * @return	AT_OK	: 正常
	 */
	int write(const TString &szData, ...);

	/**
	 * ファイル読込
	 *
	 * @param	LPCVOID pData				読込データ
	 * @param	size_t uiSize				読込サイズ
	 *
	 * @return	AT_OK	: 正常
	 */
	virtual int read(LPVOID pData, size_t uiSize);

	/**
	 * ファイル読込
	 * <br>ファイル一行分の文字列を読み込む
	 *
	 * @param	TString &szData				読込文字列
	 *
	 * @return	AT_OK	: 正常
	 */
	int read(TString &szData);

	/**
	 * ファイルサイズ取得
	 *
	 * @return		ファイルサイズ
	 */
	unsigned int getFileSize() const;

	/**
	 * EOF判定
	 *
	 * @return		true	: EOF
	 *				false	: not EOF
	 */
	bool isEof() const;

protected:
	FILE			*ml_pFile;
	TString			ml_szFileName;
};
#endif // __ATLIBFILE_H__EECA9CB2_0CC6_474E_8668_296B9B4B730B