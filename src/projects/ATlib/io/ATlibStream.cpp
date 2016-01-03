/**
 * Stream class implementation <br>
 * <b>ATlibStream.cpp</b>
 *
 * @author slowhand0309
 */
#include "ATlib/io/ATlibStream.h"

/**
 * Constructor.
 */
ATStream::ATStream()
	: ml_bOpen(false)
{
	_tsetlocale(LC_ALL, _T("Japanese"));
}

/**
 * Destructor.
 */
ATStream::~ATStream()
{
}

/**
 * Check stream open.
 *
 * @return true : open / false : not open
 */
bool ATStream::isOpen() const
{
	return ml_bOpen;
}
