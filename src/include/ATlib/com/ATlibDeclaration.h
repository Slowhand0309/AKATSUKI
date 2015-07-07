#ifndef __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
#define __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
/**
 * 共通ライブラリ 定数、構造体等の定義
 * ATlibDeclaration.h
 *
 * @author	jf-orange
 */
#include "ATlib/com/ATlibPlatform.h"

/* ----- common define ----- */
#define AT_OK									(0x00000001)								/* 正常						*/
#define AT_ERR_HANDLE							(0x90000000)								/* 無効なハンドル			*/
#define AT_ERR_LOCK								(0x90000001)								/* 排他の取得に失敗			*/
#define AT_ERR_ARGUMENTS						(0x90000002)								/* 引数不正					*/
#define AT_ERR_IOEXCEPTION						(0x90000003)								/* IO例外					*/
#define AT_ERR_CONVEXCEPTION					(0x90000004)								/* 内部変換処理例外			*/
#define AT_ERR_CONTRADICTION					(0x90000005)								/* 内部矛盾エラー			*/
#define AT_ERR_NOTFOUND							(0x90000006)								/* 存在無し					*/
#define AT_ERR_SETTINGS							(0x90000007)								/* 設定エラー				*/

#define AT_SAFE_DELETE(p)						{ if (p) { delete (p);      (p)=NULL; } }	/* 安全対策(delete)			*/
#define AT_SAFE_RELEASE(p)						{ if (p) { (p)->Release();  (p)=NULL; } }	/* Release					*/
#define AT_SAFE_DELETE_ARRAY(p)					{ if (p) { delete[] (p);    (p)=NULL; } }	/* delete[]					*/
#define AT_ARRAY_SIZE(o)						(sizeof(o)/sizeof(o[0]))					/* 配列の要素数取得			*/
#define AT_PI									(3.14159265358979323846)					/* 円周率					*/
#define	AT_EMPTY_STR							_T("")										/* 空文字					*/

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

/* マクロ等の文字化				*/
#define __TOSTR(x)								#x
#define TOSTR(macro)							__TOSTR(macro)

/* マクロ等の文字連結			*/
#define __CONCATSTR(str, x)						str##x
#define CONCATSTR(str, x)						__CONCATSTR(str, x)

/* マクロ等の文字連結拡張		*/
#define __CONCATSTREX(str, x, x2)				str##x##x2
#define CONCATSTREX(str, x, x2)					__CONCATSTREX(str, x, x2)

/* コンパイラへの警告メッセージ出力 
   指定行への移動可能 *usage : #pragma __ATMESSAGE__("out put message")	*/
#define __ATMESSAGE__(msg)						message(__FILE__"("TOSTR(__LINE__)") : "msg)

#ifdef PLATFORM_WINDOWS
/* declaration for windows					*/

/* ----- include ----- */
#include<windows.h>
#include<winbase.h>
#include<mmsystem.h>
#include<tchar.h>

/* ----- warning disable ----- */
#pragma	warning (disable: 4996)															/* 古い形式のＣ標準関数の使用に警告を出さない	*/
#pragma warning (disable: 4819)															/* 表示できない文字警告を出さない				*/
#pragma warning (disable: 4995)															/* 旧形式関数名警告を出さない					*/
#pragma warning (disable: 4482)															/* enumの限定名を許可							*/

/* ----- link lib files ----- */
#pragma comment ( lib, "strmiids.lib")
#pragma comment ( lib, "winmm.lib")
#pragma comment ( lib, "msimg32.lib")
#pragma comment	( lib, "ws2_32.lib")

#define ATSleep(t)			Sleep(1000 * t)												/* Sleep(sec)				*/
#define AT_INVALID_HANDLE	NULL														/* 無効なハンドル			*/

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
#define AT_INVALID_HANDLE	(-1)														/* 無効なハンドル			*/

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
/* ワイド文字						*/
#define __T(x) 				L##x
#define TCHAR				wchar_t
#define _TCHAR				wchar_t
#define _tsetlocale			_wsetlocale
#define _tmkdir				wmkdir
#define _vstprintf			vswprintf
#else 
/* マルチバイト文字					*/
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
typedef std::basic_string<TCHAR>					TString;								/* TCHAR型のstd::string			*/
typedef unsigned int								ATColor;								/* カラー						*/
typedef void*										ATHandle;								/* ハンドル						*/

#endif // __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
