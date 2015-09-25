#ifndef __ATLIBFILE_H__EECA9CB2_0CC6_474E_8668_296B9B4B730B
#define __ATLIBFILE_H__EECA9CB2_0CC6_474E_8668_296B9B4B730B

#include "ATlib/io/ATlibStream.h"

/**
 * �t�@�C������N���X<br>
 * <b>ATlibFile.h</b>
 *
 * @author slowhand0309
 */
class ATFile : public ATStream
{
public:
	/**
	 * �R���X�g���N�^
	 */
	ATFile();

	/**
	 * �R���X�g���N�^
	 *
	 * @param	const TString &fileName		�t�@�C������
	 * @param	const enum OpenMode eMode	���[�h
	 */
	ATFile(const TString &fileName, const enum OpenMode eMode);

	/**
	 * �f�X�g���N�^
	 */
	virtual ~ATFile();

	/**
	 * �t�@�C���I�[�v������
	 *
	 * @param	const TString &szName		�t�@�C������
	 * @param	const enum OpenMode eMode	���[�h
	 *
	 * @return	AT_OK	: ����
	 */
	virtual int open(const TString &szName, const enum OpenMode eMode);

	/**
	 * �t�@�C���N���[�Y����
	 */
	virtual void close();

	/**
	 * �t�@�C������
	 *
	 * @param	LPCVOID pData				�����f�[�^
	 * @param	size_t uiSize				�����T�C�Y
	 *
	 * @return	AT_OK	: ����
	 */
	virtual int write(LPCVOID pData, size_t uiSize);

	/**
	 * �t�@�C������
	 * <br>�t�@�C����s�����������������
	 *
	 * @param	const TString &szData		����������
	 * @param	...							�ϒ�����
	 *
	 * @return	AT_OK	: ����
	 */
	int write(const TString &szData, ...);

	/**
	 * �t�@�C���Ǎ�
	 *
	 * @param	LPCVOID pData				�Ǎ��f�[�^
	 * @param	size_t uiSize				�Ǎ��T�C�Y
	 *
	 * @return	AT_OK	: ����
	 */
	virtual int read(LPVOID pData, size_t uiSize);

	/**
	 * �t�@�C���Ǎ�
	 * <br>�t�@�C����s���̕������ǂݍ���
	 *
	 * @param	TString &szData				�Ǎ�������
	 *
	 * @return	AT_OK	: ����
	 */
	int read(TString &szData);

	/**
	 * �t�@�C���T�C�Y�擾
	 *
	 * @return		�t�@�C���T�C�Y
	 */
	unsigned int getFileSize() const;

	/**
	 * EOF����
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