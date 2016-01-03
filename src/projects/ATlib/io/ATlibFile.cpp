/**
 * ATFIle class implementation<br>
 * <b>ATlibFile.cpp</b>
 *
 * @author slowhand0309
 */
#include "ATlib/utl/ATlibStringUtl.h"
#include "ATlib/io/ATlibFile.h"

#ifdef PLATFORM_WINDOWS
#include <typeinfo.h>
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
#include <typeinfo>
#endif // PLATFORM_LINUX

#include <stdarg.h>

/**
 * Constructor.
 */
ATFile::ATFile()
	: ml_pFile(NULL)
{
}

/**
 * Constructor.
 *
 * @param	const TString &fileName file name
 * @param	const enum OpenMode eMode open mode
 */
ATFile::ATFile(const TString &fileName, const enum OpenMode eMode)
{
	ATFile();
	open(fileName, eMode);
}

/**
 * Destructor.
 */
ATFile::~ATFile()
{
	close();
}

/**
 * Open file.
 *
 * @param	const TString &szName file name
 * @param	const enum OpenMode eMode open mode
 *
 * @return	AT_OK : file opend
 */
int ATFile::open(const TString &szName, const enum OpenMode eMode)
{
	/* Open by mode */
	TString szMode;
	switch (eMode) {
		case OpenMode_ReadOnly: /* Read only */
			szMode = _T("rb");
			break;

		case OpenMode_Write: /* Write */
			szMode = _T("wb");
			break;

		case OpenMode_Append: /* Append */
			szMode = _T("ab");
			break;

		case OpenMode_TxtReadOnly: /* Read only of Text */
			szMode = _T("r");
			break;

		case OpenMode_TxtWrite: /* Write of Text */
			szMode = _T("w");
			break;

		case OpenMode_TxtAppend: /* Append of Text */
			szMode = _T("a");
			break;

		default:
			TRACE(_T("ATFile open() mode failed. %d"), eMode);
			return AT_ERR_ARGUMENTS;
	}

	try {
		/* file open */
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

/**
 * Close file.
 */
void ATFile::close()
{
	if (ml_pFile != NULL) {
		fclose(ml_pFile);
		ml_pFile = NULL;
	}

	ml_bOpen = false;
	ml_szFileName.clear();
}

/**
 * Write data to file.
 *
 * @param	LPCVOID pData write data
 * @param	size_t uiSize write size
 *
 * @return	AT_OK : write success
 */
int ATFile::write(LPCVOID pData, size_t uiSize)
{
	if (pData == NULL) {
		return AT_ERR_ARGUMENTS;
	}

	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* Lock file */
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

/**
 * Write data to file.
 * <br>write strings
 *
 * @param	const TString &szData write strings data
 * @param	... vargs
 *
 * @return	AT_OK : write success
 */
int ATFile::write(const TString &szData, ...)
{
	if (!ATStringUtl::isEmpty(szData)) {
		return AT_ERR_ARGUMENTS;
	}

	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* variable args */
	va_list vaList;
	TCHAR szBuff[_MAX_PATH] = {0};

	const TCHAR *pSrc = szData.c_str();
	va_start(vaList, pSrc);
#ifdef PLATFORM_WINDOWS
	_vstprintf_s(szBuff, _MAX_PATH, pSrc, vaList);
#else
	vsprintf(szBuff, pSrc, vaList);
#endif
	va_end(vaList);

	/* Lock file */
	if (ml_oLock.lock() != AT_OK) {
		return AT_ERR_IOEXCEPTION;
	}

	_ftprintf_s(ml_pFile, szBuff);

	ml_oLock.unlock();
	return AT_OK;
}

/**
 * Read from file.
 *
 * @param	LPCVOID pData read data
 * @param	size_t uiSize read size
 *
 * @return AT_OK : read success
 */
int ATFile::read(LPVOID pData, size_t uiSize)
{
	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* Lock file */
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

/**
 * Read from file.
 * <br>read for string
 *
 * @param TString &szData read string data
 *
 * @return AT_OK : read success
 */
int ATFile::read(TString &szData)
{
	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* Lock file */
	if (ml_oLock.lock() != AT_OK) {
		return AT_ERR_IOEXCEPTION;
	}

	TCHAR szBuff[_MAX_PATH] = {0};
	_fgetts(szBuff, _MAX_PATH, ml_pFile);
	szData = TString(szBuff);

	ml_oLock.unlock();
	return AT_OK;
}

/**
 * Get size for file.
 *
 * @return file size
 */
unsigned int ATFile::getFileSize() const
{
	unsigned int uiPos = 0;
	// Check file open
	if (isOpen() == false) {
		TRACE(_T("file not open for get file size."));
		return uiPos;
	}

	unsigned int uiCurPos = ftell(ml_pFile);

	fseek(ml_pFile, 0, SEEK_END);
    uiPos = ftell(ml_pFile);
    fseek(ml_pFile, uiCurPos, SEEK_SET);

	return uiPos;
}

/**
 * Check EOF
 *
 * @return true : EOF
 *         false : not EOF
 */
bool ATFile::isEof() const
{
	return feof(ml_pFile) == 0 ? false : true;
}
