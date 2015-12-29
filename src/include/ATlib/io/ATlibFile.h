#ifndef __ATLIBFILE_H__EECA9CB2_0CC6_474E_8668_296B9B4B730B
#define __ATLIBFILE_H__EECA9CB2_0CC6_474E_8668_296B9B4B730B

#include "ATlib/io/ATlibStream.h"

/**
 * File manage class<br>
 * <b>ATlibFile.h</b>
 *
 * @author slowhand0309
 */
class ATFile : public ATStream
{
public:
	/**
	 * Constructor.
	 */
	ATFile();

	/**
	 * Constructor.
	 *
	 * @param	const TString &fileName file name
	 * @param	const enum OpenMode eMode open mode
	 */
	ATFile(const TString &fileName, const enum OpenMode eMode);

	/**
	 * Destructor.
	 */
	virtual ~ATFile();

	/**
	 * Open file.
	 *
	 * @param	const TString &szName file name
	 * @param	const enum OpenMode eMode open mode
	 *
	 * @return	AT_OK : file opend
	 */
	virtual int open(const TString &szName, const enum OpenMode eMode);

	/**
	 * Close file.
	 */
	virtual void close();

	/**
	 * Write data to file.
	 *
	 * @param	LPCVOID pData write data
	 * @param	size_t uiSize write size
	 *
	 * @return	AT_OK : write success
	 */
	virtual int write(LPCVOID pData, size_t uiSize);

	/**
	 * Write data to file.
	 * <br>write strings
	 *
	 * @param	const TString &szData write strings data
	 * @param	... vargs
	 *
	 * @return	AT_OK : write success
	 */
	int write(const TString &szData, ...);

	/**
	 * Read from file.
	 *
	 * @param	LPCVOID pData read data
	 * @param	size_t uiSize read size
	 *
	 * @return AT_OK : read success
	 */
	virtual int read(LPVOID pData, size_t uiSize);

	/**
	 * Read from file.
	 * <br>read for string
	 *
	 * @param TString &szData read string data
	 *
	 * @return AT_OK : read success
	 */
	int read(TString &szData);

	/**
	 * Get size for file.
	 *
	 * @return file size
	 */
	unsigned int getFileSize() const;

	/**
	 * Check EOF
	 *
	 * @return true : EOF
	 *         false : not EOF
	 */
	bool isEof() const;

protected:
	FILE *ml_pFile;
	TString ml_szFileName;
};
#endif // __ATLIBFILE_H__EECA9CB2_0CC6_474E_8668_296B9B4B730B
