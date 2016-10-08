#ifndef __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188
#define __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188

#include "ATlib/io/ATlibLock.h"

/**
 * Open Stream mode.
 */
enum OpenMode {
	OpenMode_ReadOnly = 0, /* Read only */
	OpenMode_Write,	/* Write */
	OpenMode_Append, /* Append */
	OpenMode_TxtReadOnly, /* Read only of Text */
	OpenMode_TxtWrite, /* Wirite of Text */
	OpenMode_TxtAppend /* Append of Text */
};

/**
 * Specific location.(iOS, Android)
 */
enum SpecificLocation {
#if defined(PLATFORM_IOS)
    SpecificLocation_iOS_Bundle,   // /var/mobile/Applications/[UUID]/XXXXXX.app
    SpecificLocation_iOS_Document, // /var/mobile/Applications/[UUID]/Documents
#elif defined(PLATFORM_ANDROID)
    SpecificLocation_Android_App,  // /data/data/[application-id]
    SpecificLocation_Android_SD,   // sdcard
    SpecificLocation_Android_ExApp // Android/data/[application-id]/
#endif
    SpecificLocation_None = 0
};

/**
 * Stream class<br>
 * <b>ATlibStream.h</b>
 *
 * @author slowhand0309
 */
class ATStream
{
public:
	/**
	 * Constructor.
	 */
	ATStream();

	/**
	 * Destructor.
	 */
	virtual ~ATStream();

	/**
	 * Check stream open.
	 *
	 * @return true : open / false : not open
	 */
	virtual bool isOpen() const;

	/**
	 * Open stream<br>
	 * oepn stream from file name
	 *
	 * @param	szName file name
	 * @param	eMode open mode
     * @param   eLocation  specific location for mobile.
	 */
	virtual int open(const TString &szName, const enum OpenMode eMode,
                     const enum SpecificLocation eLocation = SpecificLocation_None) = 0;

	/**
	 * Close stream
	 */
	virtual void close() = 0;

	/**
	 * Write to stream
	 *
	 * @param	pData write data
	 * @param	uiSize write data size
	 */
	virtual int write(LPCVOID pData, size_t uiSize) = 0;

	/**
	 * Read from stream
	 *
	 * @param	pData read data
	 * @param	uiSize read size
	 */
	virtual int read(LPVOID pData, size_t uiSize) = 0;

protected:
	ATLock ml_oLock;
	bool ml_bOpen;
};
#endif // __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188
