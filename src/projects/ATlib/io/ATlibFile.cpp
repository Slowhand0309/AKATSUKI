#include "ATlib/utl/ATlibStringUtl.h"
#include "ATlib/io/ATlibFile.h"

#ifdef PLATFORM_WINDOWS
#include <typeinfo.h>
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
#include <typeinfo>
#endif // PLATFORM_LINUX

#include <stdarg.h>

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATFile::ATFile()
	: ml_pFile(NULL)
{
}

//********************************************************************************************
/**
 * コンストラクタ
 *
 * @param	const TString &fileName		ファイル名.
 * @param	const enum OpenMode eMode	モード.
 *
 */
//********************************************************************************************
ATFile::ATFile(const TString &fileName, const enum OpenMode eMode)
{
	ATFile();
	open(fileName, eMode);
}

//********************************************************************************************
/**
 * デストラクタ
 *
 * @param			なし.
 *
 */
//********************************************************************************************
ATFile::~ATFile()
{
	close();
}

//********************************************************************************************
/**
 * ファイルオープン
 *
 * @param	const TString &szName		ファイル名称.
 * @param	const enum OpenMode eMode	ファイルモード
 *
 * @return			AT_OK				: 正常
 *					AT_ERR_ARGUMENTS	: パラメータ不正
 *					AT_ERR_IOEXCEPTION	: IO例外
 */
//********************************************************************************************
int ATFile::open(const TString &szName, const enum OpenMode eMode)
{
	/* ファイルモード指定			*/
	TString szMode;
	switch (eMode) {
		case OpenMode::OpenMode_ReadOnly:		/* 読込専用		*/
			szMode = _T("rb");
			break;

		case OpenMode::OpenMode_Write:			/* 書込み		*/
			szMode = _T("wb");
			break;

		case OpenMode::OpenMode_Append:			/* 追加			*/
			szMode = _T("ab");
			break;

		case OpenMode::OpenMode_TxtReadOnly:		/* 読込専用		*/
			szMode = _T("r");
			break;

		case OpenMode::OpenMode_TxtWrite:			/* 書込み		*/
			szMode = _T("w");
			break;

		case OpenMode::OpenMode_TxtAppend:			/* 追加			*/
			szMode = _T("a");
			break;

		default:
			TRACE(_T("ATFile open() mode failed. %d"), eMode);
			return AT_ERR_ARGUMENTS;
	}

	try {
		/* ファイルオープン			*/
		ml_pFile = _tfopen(szName.c_str(), szMode.c_str());
		if (ml_pFile == NULL) {
			throw "";
		}
	} catch (...) {
		close();
		TRACE(_T("ATFile open() fopen failed."));
		return AT_ERR_IOEXCEPTION;
	}

	ml_bOpen = true;
	ml_szFileName = szName;

	return AT_OK;
}

//********************************************************************************************
/**
 * ファイルクローズ
 *
 * @param						なし.
 *
 * @return						なし.
 */
//********************************************************************************************
void ATFile::close()
{
	if (ml_pFile != NULL) {
		fclose(ml_pFile);
		ml_pFile = NULL;
	}

	ml_bOpen = false;
	ml_szFileName.clear();
}

//********************************************************************************************
/**
 * ファイル書込み
 *
 * @param	LPCVOID pData		書込みデータ.
 * @param	size_t uiSize		書込みサイズ.
 *
 * @return			AT_OK				: 正常
 *					AT_ERR_ARGUMENTS	: パラメータ不正
 *					AT_ERR_IOEXCEPTION	: IO例外
 */
//********************************************************************************************
int ATFile::write(LPCVOID pData, size_t uiSize)
{
	if (pData == NULL) {
		return AT_ERR_ARGUMENTS;
	}

	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* ファイル書込み		*/
	if (ml_oLock.lock() != AT_OK) {
		return AT_ERR_IOEXCEPTION;
	}

	if (fwrite(pData, uiSize, 1, ml_pFile) < 0) {
		ml_oLock.unlock();
		return AT_ERR_IOEXCEPTION;
	}
	ml_oLock.unlock();
	return AT_OK;
}

//********************************************************************************************
/**
 * ファイル書込み
 * ファイル一行分文字列を書き込む
 *
 * @param	const TString &szData		書込み文字列.
 * @param	...							可変長引数.
 *
 * @return			AT_OK				: 正常
 *					AT_ERR_ARGUMENTS	: パラメータ不正
 *					AT_ERR_IOEXCEPTION	: IO例外
 */
//********************************************************************************************
int ATFile::write(const TString &szData, ...)
{
	if (!ATStringUtl::isEmpty(szData)) {
		return AT_ERR_ARGUMENTS;
	}

	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* 可変長リストの取得	*/
	va_list		vaList;
	TCHAR		szBuff[_MAX_PATH] = {0};

	const TCHAR *pSrc = szData.c_str();	
	va_start(vaList, pSrc);
	_vstprintf_s(szBuff, _MAX_PATH, pSrc, vaList);
	va_end(vaList);

	/* ファイル書込み		*/
	if (ml_oLock.lock() != AT_OK) {
		return AT_ERR_IOEXCEPTION;
	}

	_ftprintf_s(ml_pFile, szBuff);

	ml_oLock.unlock();
	return AT_OK;
}

//********************************************************************************************
/**
 * ファイル読込み
 *
 * @param	LPVOID pData		読込みデータ.
 * @param	size_t uiSize		読込みサイズ.
 *
 * @return			AT_OK				: 正常
 *					AT_ERR_ARGUMENTS	: パラメータ不正
 *					AT_ERR_IOEXCEPTION	: IO例外
 */
//********************************************************************************************
int ATFile::read(LPVOID pData, size_t uiSize)
{
	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* ファイル読込み		*/
	if (ml_oLock.lock() != AT_OK) {
		return AT_ERR_IOEXCEPTION;
	}

	if (fread(pData, uiSize, 1, ml_pFile) < 0) {
		ml_oLock.unlock();
		return AT_ERR_IOEXCEPTION;
	}

	ml_oLock.unlock();
	return AT_OK;
}

//********************************************************************************************
/**
 * ファイル読込み
 * ファイル一行分の文字列を読み込む
 *
 * @param	TString &szData		読込み文字列.
 *
 * @return			AT_OK				: 正常
 *					AT_ERR_ARGUMENTS	: パラメータ不正
 *					AT_ERR_IOEXCEPTION	: IO例外
 */
//********************************************************************************************
int ATFile::read(TString &szData)
{
	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* ファイル読込み		*/
	if (ml_oLock.lock() != AT_OK) {
		return AT_ERR_IOEXCEPTION;
	}

	TCHAR szBuff[_MAX_PATH] = {0};
	_fgetts(szBuff, _MAX_PATH, ml_pFile);
	szData = TString(szBuff);

	ml_oLock.unlock();
	return AT_OK;
}

//********************************************************************************************
/**
 * ファイルサイズ取得
 *
 * @param			なし.
 *
 * @return			ファイルサイズ(unsigned int)
 *					失敗した場合は0を返す
 */
//********************************************************************************************
unsigned int ATFile::getFileSize() const
{
	unsigned int uiPos = 0;
	// ファイル状態チェック
	if (isOpen() == false) {
		TRACE(_T("file not open for get file size."));
		return uiPos;
	}
	// 現在のファイルポジション取得
	unsigned int uiCurPos = ftell(ml_pFile);
	// ファイル末端まで移動
	fseek(ml_pFile, 0, SEEK_END);
	// ファイル全体のサイズを取得
    uiPos = ftell(ml_pFile);
	// 元の場所に戻す
    fseek(ml_pFile, uiCurPos, SEEK_SET);

	return uiPos;
}

//********************************************************************************************
/**
 * EOF判定
 *
 * @param			なし.
 *
 * @return			true	: EOF
 *					falses	: not EOF
 */
//********************************************************************************************
bool ATFile::isEof() const
{
	return feof(ml_pFile) == 0 ? false : true;
}