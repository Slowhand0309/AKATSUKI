#ifndef __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188
#define __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188

#include "ATlib/io/ATlibLock.h"

const enum OpenMode {
	OpenMode_ReadOnly = 0,	/* 読込専用(バイナリ)			*/
	OpenMode_Write,			/* 読み書き(バイナリ)			*/
	OpenMode_Append,		/* 追加書込(バイナリ)			*/
	OpenMode_TxtReadOnly,	/* 読込専用(テキスト)			*/
	OpenMode_TxtWrite,		/* 読み書き(テキスト)			*/
	OpenMode_TxtAppend		/* 追加書込(テキスト)			*/
};

class ATStream
{
public:
	/**
	 * コンストラクタ
	 */
	ATStream();

	/**
	 * デストラクタ
	 */
	virtual ~ATStream();

	/**
	 * ストリームが開かれているか
	 *
	 * @return true	:	開いている / false	: 開いていない
	 */
	virtual bool isOpen() const;

	/**
	 * オープン処理<br>
	 * 純粋仮想関数
	 *
	 * @param	const TString &szName		ストリーム名
	 * @param	const enum OpenMode eMode	モード
	 */
	virtual int open(const TString &szName, const enum OpenMode eMode) = 0;

	/**
	 * クローズ処理<br>
	 * 純粋仮想関数
	 */
	virtual void close() = 0;

	/**
	 * ストリームへ書込み<br>
	 * 純粋仮想関数
	 *
	 * @param		LPCVOID pData			出力データ
	 * @param		size_t uiSize			出力サイズ
	 */
	virtual int write(LPCVOID pData, size_t uiSize) = 0;

	/**
	 * ストリームから読込み<br>
	 * 純粋仮想関数
	 *
	 * @param		LPCVOID pData			読込データ
	 * @param		size_t uiSize			読込サイズ
	 */
	virtual int read(LPVOID pData, size_t uiSize) = 0;

protected:
	ATLock			ml_oLock;
	bool			ml_bOpen;
};
#endif // __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188
