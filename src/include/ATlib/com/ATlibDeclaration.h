#ifndef __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
#define __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
/**
 * Common declare values
 * ATlibDeclaration.h
 *
 * @author	slowhand0309
 */

/* ----- common define ----- */
#define AT_OK                     (0x00000001)    /* Successed           */
#define AT_ERR_HANDLE             (0x90000000)    /* Handle error        */
#define AT_ERR_LOCK               (0x90000001)    /* Lock error          */
#define AT_ERR_ARGUMENTS          (0x90000002)    /* Arguments error     */
#define AT_ERR_IOEXCEPTION        (0x90000003)    /* IO exception        */
#define AT_ERR_CONVEXCEPTION      (0x90000004)    /* Convert exception   */
#define AT_ERR_CONTRADICTION      (0x90000005)    /* Contradiction       */
#define AT_ERR_NOTFOUND           (0x90000006)    /* Not found resources */
#define AT_ERR_SETTINGS           (0x90000007)    /* Settings error      */

/* ----- about opengl ----- */
#define AT_ERR_OPENGL_INIT        (0x90001000)    /* OpenGL init error   */

/* ----- about directx ----- */
#define AT_ERR_DIRECTX_INIT       (0x90010000)    /* DirectX init error  */

#define AT_SAFE_DELETE(p)         { if (p) { delete (p);      (p)=NULL; } } /* Safe delete       */
#define AT_SAFE_RELEASE(p)        { if (p) { (p)->Release();  (p)=NULL; } } /* Safe Release      */
#define AT_SAFE_DELETE_ARRAY(p)   { if (p) { delete[] (p);    (p)=NULL; } } /* Safe delete array */
#define AT_ARRAY_SIZE(o)          (sizeof(o)/sizeof(o[0]))                  /* Size of array     */
#define AT_PI                     (3.14159265358979323846)                  /* PI                */
#define	AT_EMPTY_STR              _T("")                                    /* Empty string      */

#define BUFF_SIZE                 (1024)

#ifndef max
#define max(a, b)                 (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b)                 (((a) < (b)) ? (a) : (b))
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

/* to text macro */
#define __TOSTR(x)                       #x
#define TOSTR(macro)                     __TOSTR(macro)

/* concat text */
#define __CONCATSTR(str, x)              str##x
#define CONCATSTR(str, x)                __CONCATSTR(str, x)

/* concat text multiple */
#define __CONCATSTREX(str, x, x2)        str##x##x2
#define CONCATSTREX(str, x, x2)          __CONCATSTREX(str, x, x2)

/* print message
 * usage : #pragma __ATMESSAGE__("out put message") */
#define __ATMESSAGE__(msg)						message(__FILE__"(" TOSTR(__LINE__)") : " msg)

#if defined(DEBUG) || defined(_DEBUG)
#define ATASSERT(x)  assert(x)
#else
#define ATASSERT(x)
#endif

#include "ATlib/com/ATlibPlatform.h"


#ifdef PLATFORM_WINDOWS
/* declaration for windows */

/* ----- include ----- */
#include<windows.h>
#include<winbase.h>
#include<mmsystem.h>
#include<tchar.h>

/* ----- warning disable ----- */
#pragma	warning (disable: 4996)
#pragma warning (disable: 4819)
#pragma warning (disable: 4995)
#pragma warning (disable: 4482)

/* ----- link lib files ----- */
#pragma comment (lib, "strmiids.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "msimg32.lib")
#pragma comment	(lib, "ws2_32.lib")

#define ATSleep(t)                     Sleep(1000 * t) /* Sleep(sec)     */
#define AT_INVALID_HANDLE              NULL            /* Invalid handle */


#ifndef TRACE
#ifdef _DEBUG
#define TRACE(...) \
		{ \
			TCHAR str[_MAX_PATH] = {0}; \
			TCHAR info[_MAX_PATH] = {0}; \
			_stprintf(str, __VA_ARGS__); \
			OutputDebugString(str); \
			_stprintf(info, _T("\n %ls(%d)\n"), _T(__FILE__), __LINE__); \
			OutputDebugString(fin); \
		}
#else
#define TRACE(...) \
		{ \
			TCHAR str[_MAX_PATH] = {0}; \
			_stprintf(str, __VA_ARGS__); \
			OutputDebugString(str); \
		}
#endif // _DEBUG
#endif // TRACE

/* ----- Memory check ----- */
#if defined(DEBUG) || defined(_DEBUG)
#define MemoryLeakCheck      _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF )
#else
#define MemoryLeakCheck
#endif // DEBUG

#else // PLATFORM_WINDOWS

/* declaration for Linux Mac Other */
#include <sys/types.h>
#include <sys/stat.h>

#define ATSleep(t)                     sleep(t) /* Sleep(sec)     */
#define AT_INVALID_HANDLE              (-1)     /* Invalid handle */

#ifndef CONST
#define CONST const
#endif

#define far
#define near

typedef unsigned long        DWORD;
typedef int                  BOOL;
typedef unsigned char        BYTE;
typedef unsigned short       WORD;
typedef float                FLOAT;
typedef FLOAT*               PFLOAT;
typedef BOOL near*           PBOOL;
typedef BOOL far*            LPBOOL;
typedef BYTE near*           PBYTE;
typedef BYTE far*            LPBYTE;
typedef int near*            PINT;
typedef int far*             LPINT;
typedef WORD near*           PWORD;
typedef WORD far*            LPWORD;
typedef long far*            LPLONG;
typedef DWORD near*          PDWORD;
typedef DWORD far*           LPDWORD;
typedef void far*            LPVOID;
typedef CONST void far*      LPCVOID;
typedef void*                HANDLE;
typedef int                  INT;
typedef unsigned int         UINT;
typedef unsigned int*        PUINT;
typedef long                 HRESULT;

#ifndef FALSE
#define FALSE       0
#endif

#ifndef TRUE
#define TRUE        1
#endif

#ifndef NULL
#define NULL        0
#endif

#ifdef _UNICODE
/* UNICODE */
#define __T(x)              L##x
#define TCHAR               wchar_t
#define _TCHAR              wchar_t
#define _tsetlocale         _wsetlocale
#define _tmkdir             wmkdir
#define _vstprintf          vswprintf
#define _tstat              _wstat
#else
/* MLUTIBYTE */
#define __T(x)              x
#define TCHAR               char
#define _TCHAR              char
#define _tsetlocale         setlocale
#define _vstprintf_s        vsprintf_l
#define _ftprintf_s         fprintf
#define _tmkdir(x)          mkdir(x, S_IRUSR | S_IRGRP | S_IXUSR | S_IXGRP | S_IWUSR | S_IWGRP)
#define	_tprintf            printf
#define _ftprintf           fprintf
#define	_stprintf           sprintf
#define	_sntprintf          _snprintf
#define	_vtprintf           vprintf
#define	_vftprintf          vfprintf
#define _vstprintf          vsprintf
#define	_vsntprintf         _vsnprintf
#define	_tscanf             scanf
#define	_ftscanf            fscanf
#define	_stscanf            sscanf
#define	_fgettc             fgetc
#define	_fgettchar          _fgetchar
#define	_fgetts             fgets
#define	_fputtc             fputc
#define	_fputtchar          _fputchar
#define	_fputts             fputs
#define	_tfopen             fopen
#define	_tgetenv            getenv
#define	_gettc              getc
#define	_getts              gets
#define	_puttc              putc
#define	_putts              puts
#define	_ungettc            ungetc
#define	_tcstod             strtod
#define	_tcstol             strtol
#define _tcstoul            strtoul
#define	_itot               _itoa
#define	_ltot               _ltoa
#define	_ultot              _ultoa
#define	_ttoi               atoi
#define	_ttol               atol
#define	_tcscat             strcat
#define _tcschr             strchr
#define _tcscmp             strcmp
#define _tcscpy             strcpy
#define _tcscspn            strcspn
#define	_tcslen             strlen
#define	_tcsncat            strncat
#define	_tcsncmp            strncmp
#define	_tcsncpy            strncpy
#define	_tcspbrk            strpbrk
#define	_tcsrchr            strrchr
#define _tcsspn             strspn
#define	_tcsstr             strstr
#define _tcstok             strtok
#define	_tcsdup             _strdup
#define	_tcsicmp            _stricmp
#define	_tcsnicmp           _strnicmp
#define	_tcsnset            _strnset
#define	_tcsrev             _strrev
#define _tcsset             _strset
#define	_tcslwr             _strlwr
#define	_tcsupr             _strupr
#define	_tcsxfrm            strxfrm
#define	_tcscoll            strcoll
#define	_tcsicoll           _stricoll
#define	_istalpha           isalpha
#define	_istupper           isupper
#define	_istlower           islower
#define	_istdigit           isdigit
#define	_istxdigit          isxdigit
#define	_istspace           isspace
#define	_istpunct           ispunct
#define	_istalnum           isalnum
#define	_istprint           isprint
#define	_istgraph           isgraph
#define	_istcntrl           iscntrl
#define	_istascii           isascii
#define _totupper           toupper
#define	_totlower           tolower
#define	_tasctime           asctime
#define	_tctime             ctime
#define	_tstrdate           _strdate
#define	_tstrtime           _strtime
#define	_tutime             _utime
#define _tcsftime           strftime
#define _tcsdec             _strdec
#define _tcsinc             _strinc
#define _tcsnbcnt           _strncnt
#define _tcsnccnt           _strncnt
#define _tcsnextc           _strnextc
#define _tcsninc            _strninc
#define _tcsspnp            _strspnp
#define _tchmod             _chmod
#define _tcreat             _creat
#define _tfindfirst         _findfirst
#define _tfindnext          _findnext
#define _tmktemp            _mktemp
#define _topen              _open
#define _taccess            _access
#define _tremove            remove
#define _trename            rename
#define _tsopen             _sopen
#define _tsetlocale         setlocale
#define _tunlink            _unlink
#define _tstat              stat
#define _tfinddata_t        _finddata_t
#define _strdec(_str1, _str2) ((_str1)>=(_str2) ? NULL : (_str2)-1)
#define _strinc(_str)  ((_str)+1)
#define _strnextc(_str) ((unsigned int) *(_str))
#define _strninc(_str, _inc) (((_str)+(_inc)))
#define _strncnt(_str, _cnt) ((strlen(_str)>_cnt) ? _count : strlen(_str))
#define _strspnp(_str1, _str2) ((*((_str1)+strspn(_str1,_str2))) ? ((_str1)+strspn(_str1,_str2)) : NULL)


#endif // _UNICODE

#define _T(x)                                __T(x)
#define _MAX_PATH                            (255)
#define _MAX_DIR                             (255)
#define _MAX_FNAME                           (255)
#define _MAX_EXT                             (128)
#define SUCCEEDED(hr)                        (((HRESULT)(hr)) >= 0)
#define FAILED(hr)                           (((HRESULT)(hr)) < 0)
#define MessageBox(a,b,c,d)
#define ZeroMemory(Destination,Length)       memset((Destination),0,(Length))


#ifndef TRACE
#ifdef _DEBUG
#define TRACE(...) \
		{ \
			_tprintf(__VA_ARGS__); \
			_tprintf(_T("\n%s(%d)\n"), _T(__FILE__), __LINE__); \
		}
#else
#define TRACE(...) \
		{ \
			_tprintf(__VA_ARGS__); \
			_tprintf("\n"); \
		}
#endif // _DEBUG
#endif // TRACE

#endif // PLATFORM_WINDOWS

/* ----- common typedef ----- */
typedef std::basic_string<TCHAR>    TString;  /* TCHAR std::string */
typedef unsigned int                ATColor;  /* Color */
typedef void*                       ATHandle; /* Handle */

#endif // __ATLIBDECLARATION_H__D3225B8E_B222_446A_BC44_39C2B60386F2
