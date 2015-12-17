/**
 * �t�@�C�����������N���X<br>
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

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATFile::ATFile()
	: ml_pFile(NULL)
{
}

//********************************************************************************************
/**
 * �R���X�g���N�^
 *
 * @param	const TString &fileName		�t�@�C����.
 * @param	const enum OpenMode eMode	���[�h.
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
 * �f�X�g���N�^
 *
 * @param			�Ȃ�.
 *
 */
//********************************************************************************************
ATFile::~ATFile()
{
	close();
}

//********************************************************************************************
/**
 * �t�@�C���I�[�v��
 *
 * @param	const TString &szName		�t�@�C������.
 * @param	const enum OpenMode eMode	�t�@�C�����[�h
 *
 * @return			AT_OK				: ����
 *					AT_ERR_ARGUMENTS	: �p�����[�^�s��
 *					AT_ERR_IOEXCEPTION	: IO���O
 */
//********************************************************************************************
int ATFile::open(const TString &szName, const enum OpenMode eMode)
{
	/* �t�@�C�����[�h�w��			*/
	TString szMode;
	switch (eMode) {
		case OpenMode_ReadOnly:		/* �Ǎ����p		*/
			szMode = _T("rb");
			break;

		case OpenMode_Write:			/* ������		*/
			szMode = _T("wb");
			break;

		case OpenMode_Append:			/* �ǉ�			*/
			szMode = _T("ab");
			break;

		case OpenMode_TxtReadOnly:		/* �Ǎ����p		*/
			szMode = _T("r");
			break;

		case OpenMode_TxtWrite:			/* ������		*/
			szMode = _T("w");
			break;

		case OpenMode_TxtAppend:			/* �ǉ�			*/
			szMode = _T("a");
			break;

		default:
			TRACE(_T("ATFile open() mode failed. %d"), eMode);
			return AT_ERR_ARGUMENTS;
	}

	try {
		/* �t�@�C���I�[�v��			*/
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
 * �t�@�C���N���[�Y
 *
 * @param						�Ȃ�.
 *
 * @return						�Ȃ�.
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
 * �t�@�C��������
 *
 * @param	LPCVOID pData		�����݃f�[�^.
 * @param	size_t uiSize		�����݃T�C�Y.
 *
 * @return			AT_OK				: ����
 *					AT_ERR_ARGUMENTS	: �p�����[�^�s��
 *					AT_ERR_IOEXCEPTION	: IO���O
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

	/* �t�@�C��������		*/
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
 * �t�@�C��������
 * �t�@�C�����s������������������
 *
 * @param	const TString &szData		�����ݕ�����.
 * @param	...							�ϒ�����.
 *
 * @return			AT_OK				: ����
 *					AT_ERR_ARGUMENTS	: �p�����[�^�s��
 *					AT_ERR_IOEXCEPTION	: IO���O
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

	/* �ϒ����X�g�̎擾	*/
	va_list		vaList;
	TCHAR		szBuff[_MAX_PATH] = {0};

	const TCHAR *pSrc = szData.c_str();
	va_start(vaList, pSrc);
#ifdef PLATFORM_WINDOWS
	_vstprintf_s(szBuff, _MAX_PATH, pSrc, vaList);
#else
	vsprintf(szBuff, pSrc, vaList);
#endif
	va_end(vaList);

	/* �t�@�C��������		*/
	if (ml_oLock.lock() != AT_OK) {
		return AT_ERR_IOEXCEPTION;
	}

	_ftprintf_s(ml_pFile, szBuff);

	ml_oLock.unlock();
	return AT_OK;
}

//********************************************************************************************
/**
 * �t�@�C���Ǎ���
 *
 * @param	LPVOID pData		�Ǎ��݃f�[�^.
 * @param	size_t uiSize		�Ǎ��݃T�C�Y.
 *
 * @return			AT_OK				: ����
 *					AT_ERR_ARGUMENTS	: �p�����[�^�s��
 *					AT_ERR_IOEXCEPTION	: IO���O
 */
//********************************************************************************************
int ATFile::read(LPVOID pData, size_t uiSize)
{
	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* �t�@�C���Ǎ���		*/
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
 * �t�@�C���Ǎ���
 * �t�@�C�����s���̕��������ǂݍ���
 *
 * @param	TString &szData		�Ǎ��ݕ�����.
 *
 * @return			AT_OK				: ����
 *					AT_ERR_ARGUMENTS	: �p�����[�^�s��
 *					AT_ERR_IOEXCEPTION	: IO���O
 */
//********************************************************************************************
int ATFile::read(TString &szData)
{
	if (!isOpen()) {
		return AT_ERR_IOEXCEPTION;
	}

	/* �t�@�C���Ǎ���		*/
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
 * �t�@�C���T�C�Y�擾
 *
 * @param			�Ȃ�.
 *
 * @return			�t�@�C���T�C�Y(unsigned int)
 *					���s�����ꍇ��0���Ԃ�
 */
//********************************************************************************************
unsigned int ATFile::getFileSize() const
{
	unsigned int uiPos = 0;
	// �t�@�C�����ԃ`�F�b�N
	if (isOpen() == false) {
		TRACE(_T("file not open for get file size."));
		return uiPos;
	}
	// ���݂̃t�@�C���|�W�V�����擾
	unsigned int uiCurPos = ftell(ml_pFile);
	// �t�@�C�����[�܂ňړ�
	fseek(ml_pFile, 0, SEEK_END);
	// �t�@�C���S�̂̃T�C�Y���擾
    uiPos = ftell(ml_pFile);
	// ���̏ꏊ�ɖ߂�
    fseek(ml_pFile, uiCurPos, SEEK_SET);

	return uiPos;
}

//********************************************************************************************
/**
 * EOF����
 *
 * @param			�Ȃ�.
 *
 * @return			true	: EOF
 *					falses	: not EOF
 */
//********************************************************************************************
bool ATFile::isEof() const
{
	return feof(ml_pFile) == 0 ? false : true;
}
