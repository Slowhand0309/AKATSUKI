#ifndef __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188
#define __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188

#include "ATlib/io/ATlibLock.h"

const enum OpenMode {
	OpenMode_ReadOnly = 0,	/* �Ǎ���p(�o�C�i��)			*/
	OpenMode_Write,			/* �ǂݏ���(�o�C�i��)			*/
	OpenMode_Append,		/* �ǉ�����(�o�C�i��)			*/
	OpenMode_TxtReadOnly,	/* �Ǎ���p(�e�L�X�g)			*/
	OpenMode_TxtWrite,		/* �ǂݏ���(�e�L�X�g)			*/
	OpenMode_TxtAppend		/* �ǉ�����(�e�L�X�g)			*/
};

class ATStream
{
public:
	/**
	 * �R���X�g���N�^
	 */
	ATStream();

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATStream();

	/**
	 * �X�g���[�����J����Ă��邩
	 *
	 * @return true	:	�J���Ă��� / false	: �J���Ă��Ȃ�
	 */
	virtual bool isOpen() const;

	/**
	 * �I�[�v������<br>
	 * �������z�֐�
	 *
	 * @param	const TString &szName		�X�g���[����
	 * @param	const enum OpenMode eMode	���[�h
	 */
	virtual int open(const TString &szName, const enum OpenMode eMode) = 0;

	/**
	 * �N���[�Y����<br>
	 * �������z�֐�
	 */
	virtual void close() = 0;

	/**
	 * �X�g���[���֏�����<br>
	 * �������z�֐�
	 *
	 * @param		LPCVOID pData			�o�̓f�[�^
	 * @param		size_t uiSize			�o�̓T�C�Y
	 */
	virtual int write(LPCVOID pData, size_t uiSize) = 0;

	/**
	 * �X�g���[������Ǎ���<br>
	 * �������z�֐�
	 *
	 * @param		LPCVOID pData			�Ǎ��f�[�^
	 * @param		size_t uiSize			�Ǎ��T�C�Y
	 */
	virtual int read(LPVOID pData, size_t uiSize) = 0;

protected:
	ATLock			ml_oLock;
	bool			ml_bOpen;
};
#endif // __ATLIBSTREAM_H__EFBB0FD1_1513_4126_96DF_0EF7815D5188
