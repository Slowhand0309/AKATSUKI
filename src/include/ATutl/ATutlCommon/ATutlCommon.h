// ATutlCommon.h : ATutlCommon.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

/* ----- header include ----- */
#include "resource.h"		// ���C�� �V���{��
#include "ATutl/ATutlCommon/ATutlListCtrl.h"
#include "ATutl/ATutlCommon/ATutlProfile.h"
#include "ATutl/ATutlCommon/ATutlFileBrowser.h"
#include "ATutl/ATutlCommon/ATutlBaseThread.h"

/* ----- define  ----- */
#define ERROR_MSG_TITLE					_T("�G���[")
#define WARNING_MSG_TITLE				_T("�x��")
#define INFO_MSG_TITLE					_T("���")
#define QEUSTION_MSG_TITLE				_T("�m�F")

/* ----- define utilitys ----- */
#define ATMessageBoxError(msg)			MessageBox(msg, ERROR_MSG_TITLE, MB_OK | MB_ICONERROR)
#define ATMessageBoxWarning(msg)		MessageBox(msg, WARNING_MSG_TITLE, MB_OK | MB_ICONEXCLAMATION)
#define ATMessageBoxInfo(msg)			MessageBox(msg, INFO_MSG_TITLE, MB_OK | MB_ICONINFORMATION)
#define ATMessageBoxQuestion(msg)		MessageBox(msg, QEUSTION_MSG_TITLE, MB_YESNO | MB_ICONINFORMATION)

/* TString����CString�֕ϊ�����		*/
#define T2CString(t)					CString(t.c_str())
/* CString����TString�֕ϊ�����		*/
#define	C2TString(c)					TString(c)

// CATutlCommonApp
// ���̃N���X�̎����Ɋւ��Ă� ATutlCommon.cpp ���Q�Ƃ��Ă��������B
//

class CATutlCommonApp : public CWinApp
{
public:
	CATutlCommonApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
