#ifndef __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
#define __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
/**
 * ���ʃ��C�u���� �萔�A�\���̓��̒�`
 * ATlibDeclaration.h
 *
 * @author	jf-orange
 */
#include "ATlib/com/ATlibPlatform.h"

/* ----- common define ----- */
#define AT_OK									(0x00000001)								/* ����						*/
#define AT_ERR_HANDLE							(0x90000000)								/* �����ȃn���h��			*/
#define AT_ERR_LOCK								(0x90000001)								/* �r���̎擾�Ɏ��s			*/
#define AT_ERR_ARGUMENTS						(0x90000002)								/* �����s��					*/
#define AT_ERR_IOEXCEPTION						(0x90000003)								/* IO��O					*/
#define AT_ERR_CONVEXCEPTION					(0x90000004)								/* �����ϊ�������O			*/
#define AT_ERR_CONTRADICTION					(0x90000005)								/* ���������G���[			*/
#define AT_ERR_NOTFOUND							(0x90000006)								/* ���ݖ���					*/
#define AT_ERR_SETTINGS							(0x90000007)								/* �ݒ�G���[				*/

#define AT_SAFE_DELETE(p)						{ if (p) { delete (p);      (p)=NULL; } }	/* ���S�΍�(delete)			*/
#define AT_SAFE_RELEASE(p)						{ if (p) { (p)->Release();  (p)=NULL; } }	/* Release					*/
#define AT_SAFE_DELETE_ARRAY(p)					{ if (p) { delete[] (p);    (p)=NULL; } }	/* delete[]					*/
#define AT_ARRAY_SIZE(o)						(sizeof(o)/sizeof(o[0]))					/* �z��̗v�f���擾			*/
#define AT_PI									(3.14159265358979323846)					/* �~����					*/
#define	AT_EMPTY_STR							_T("")										/* �󕶎�					*/

#ifndef max
#define max(a,b)								(((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)								(((a) < (b)) ? (a) : (b))
#endif

/* ----- define iostream ---- */
#ifndef __TOUT__
#define __TOUT__

#if defined(UNICODE) || defined(_UNICODE)
# define tout std::wcout
# define tin std::wcin
# define terr std::wcerr
# define tlog std::wclog
# define tofstream std::wofstream
# define tifstream std::wifstream
#else
# define tout std::cout
# define tin std::cin
# define terr std::cerr
# define tlog std::clog
# define tofstream std::ofstream
# define tifstream std::ifstream
#endif

#endif // __TOUT__

/* �}�N�����̕�����				*/
#define __TOSTR(x)								#x
#define TOSTR(macro)							__TOSTR(macro)

/* �}�N�����̕����A��			*/
#define __CONCATSTR(str, x)						str##x
#define CONCATSTR(str, x)						__CONCATSTR(str, x)

/* �}�N�����̕����A���g��		*/
#define __CONCATSTREX(str, x, x2)				str##x##x2
#define CONCATSTREX(str, x, x2)					__CONCATSTREX(str, x, x2)

/* �R���p�C���ւ̌x�����b�Z�[�W�o�� 
   �w��s�ւ̈ړ��\ *usage : #pragma __ATMESSAGE__("out put message")	*/
#define __ATMESSAGE__(msg)						message(__FILE__"("TOSTR(__LINE__)") : "msg)

#ifdef PLATFORM_WINDOWS
/* declaration for windows					*/

/* ----- include ----- */
#include<windows.h>
#include<winbase.h>
#include<mmsystem.h>
#include<tchar.h>

/* ----- warning disable ----- */
#pragma	warning (disable: 4996)															/* �Â��`���̂b�W���֐��̎g�p�Ɍx�����o���Ȃ�	*/
#pragma warning (disable: 4819)															/* �\���ł��Ȃ������x�����o���Ȃ�				*/
#pragma warning (disable: 4995)															/* ���`���֐����x�����o���Ȃ�					*/
#pragma warning (disable: 4482)															/* enum�̌��薼������							*/

/* ----- link lib files ----- */
#pragma comment ( lib, "strmiids.lib")
#pragma comment ( lib, "winmm.lib")
#pragma comment ( lib, "msimg32.lib")
#pragma comment	( lib, "ws2_32.lib")

#define ATSleep(t)			Sleep(1000 * t)												/* Sleep(sec)				*/
#define AT_INVALID_HANDLE	NULL														/* �����ȃn���h��			*/

#ifndef TRACE
#define TRACE(str, ...) \
		{ \
			TCHAR c[_MAX_PATH] = {0}; \
			TCHAR fin[_MAX_PATH] = {0}; \
			_stprintf(c, str, __VA_ARGS__); \
			_stprintf(fin, _T("File:[%ls]\nLine:[%d]\nMsg:[%ls]\n"), _T(__FILE__), __LINE__, c); \
			OutputDebugString( fin ); \
		}

#endif // TRACE

#else
/* declaration for Linux Mac Other			*/
#include <sys/types.h>
#include <sys/stat.h>

#define ATSleep(t)			sleep(t)													/* Sleep(sec)				*/
#define AT_INVALID_HANDLE	(-1)														/* �����ȃn���h��			*/

#ifndef CONST
#define CONST				const
#endif

#define far
#define near

typedef unsigned long		DWORD;
typedef int					BOOL;
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef float				FLOAT;
typedef FLOAT				*PFLOAT;
typedef BOOL near			*PBOOL;
typedef BOOL far			*LPBOOL;
typedef BYTE near			*PBYTE;
typedef BYTE far			*LPBYTE;
typedef int near			*PINT;
typedef int far				*LPINT;
typedef WORD near			*PWORD;
typedef WORD far			*LPWORD;
typedef long far			*LPLONG;
typedef DWORD near			*PDWORD;
typedef DWORD far			*LPDWORD;
typedef void far			*LPVOID;
typedef CONST void far		*LPCVOID;
typedef void				*HANDLE;
typedef int					INT;
typedef unsigned int		UINT;
typedef unsigned int		*PUINT;
typedef long				HRESULT;

#ifndef FALSE
#define FALSE				0
#endif

#ifndef TRUE
#define TRUE				1
#endif

#define NULL				0

#ifdef _UNICODE
/* ���C�h����						*/
#define __T(x) 				L##x
#define TCHAR				wchar_t
#define _TCHAR				wchar_t
#define _tsetlocale			_wsetlocale
#define _tmkdir				wmkdir
#define _vstprintf			vswprintf
#else 
/* �}���`�o�C�g����					*/
#define __T(x)				x
#define TCHAR				char
#define _TCHAR				char
#define _stprintf			sprintf
#define _tsetlocale			setlocale
#define _tmkdir(x)			mkdir(x, S_IRUSR | S_IRGRP | S_IXUSR | S_IXGRP | S_IWUSR | S_IWGRP)
#define _vstprintf			vsprintf
#endif // _UNICODE

#define _T(x) __T(x)

#define SUCCEEDED(hr)								(((HRESULT)(hr)) >= 0)
#define FAILED(hr)									(((HRESULT)(hr)) < 0)
#define MessageBox(a,b,c,d)	
#define ZeroMemory(Destination,Length)				memset((Destination),0,(Length))

#ifndef TRACE
#define TRACE( str, ... ) \
		{ \
			TCHAR c[_MAX_PATH] = {0}; \
			TCHAR fin[_MAX_PATH] = {0}; \
			_stprintf(c, str, __VA_ARGS__); \
			_stprintf(fin, _T("File:[%ls]\nLine:[%d]\nMsg:[%ls]\n"), _T(__FILE__), __LINE__, c); \
			printf( fin ); \
		}

#endif // TRACE
#endif // PLATFORM_WINDOWS

/* ----- common typedef ----- */
typedef std::basic_string<TCHAR>					TString;								/* TCHAR�^��std::string			*/
typedef unsigned int								ATColor;								/* �J���[						*/
typedef void*										ATHandle;								/* �n���h��						*/

#endif // __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
