#include "ATlib/io/ATlibStream.h"

ATStream::ATStream()
	: ml_bOpen(false)
{
	_tsetlocale(LC_ALL, _T("Japanese"));
}

ATStream::~ATStream()
{
}

bool ATStream::isOpen() const
{
	return ml_bOpen;
}