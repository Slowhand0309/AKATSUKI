#ifndef __ATLIBPLATFORM_H__1305AFF2_6224_47D7_B210_F2A72852FB69
#define __ATLIBPLATFORM_H__1305AFF2_6224_47D7_B210_F2A72852FB69
/**
 * Declare for cross platform.<br>
 * ATlibPlatform.h
 *
 * @author	slowhand0309
 */

/* Define for platform */
#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS		1      
    #define PLATFORM_NAME			"Windows"
#elif defined(__APPLE__) || defined(__MACH__)
    #define PLATFORM_MACINTOSH		1        
    #define PLATFORM_NAME			"Macintosh"
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__CYGWIN__)
    #define PLATFORM_LINUX			1         
    #define PLATFORM_NAME			"Linux"
#else
    #define PLATFORM_SOMETHINGELSE	1         
    #define PLATFORM_NAME			"Other"
#endif


/* 32/64 bit */
#if (defined(_WIN64) || defined(WIN64))
    #define PLATFORM_BITS       64
// Macintosh
#elif (defined(__LP64__) || defined(_LP64) || defined(__ppc64__))
    #define PLATFORM_BITS       64
// Linux
#elif (defined(__x86_64__) || defined(__64BIT__) || (__WORDSIZE == 64))
    #define PLATFORM_BITS       64
#else
    #define PLATFORM_BITS       32
#endif

/* Compiler */
#ifdef _MSC_VER // Visual Studio
	#define COMPILER_VERSION       _MSC_VER

	#if (COMPILER_VERSION >= 1600)
		#define COMPILER		COMPILER_VS2010
		#define COMPILER_NAME	   "Visual Studio 2010"
	#elif (COMPILER_VERSION >= 1500)
		#define COMPILER        COMPILER_VS2008
		#define COMPILER_NAME      "Visual Studio 2008"
	#elif (COMPILER_VERSION >= 1400)
		#define COMPILER        COMPILER_VS2005
		#define COMPILER_NAME      "Visual Studio 2005"
	#elif (COMPILER_VERSION >= 1300)
		#define COMPILER        COMPILER_VSDOTNET
		#define COMPILER_NAME      "Visual Studio .NET"
	#elif (COMPILER_VERSION >= 1200)
		#define COMPILER        COMPILER_VS6
		#define COMPILER_NAME      "Visual Studio 6"
	#else
		#error This version of Visual Studio is not supported.
	#endif

#elif defined(__GNUC__) // G++ GNU
        // TODO: get actual compiler information for G++
        #define COMPILER_VERSION       (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
        #define COMPILER_NAME       "G++"
#endif

/* Option for Visual Studio */
#ifdef PLATFORM_WINDOWS
	// Support for Windows 98
	#if COMPILER_VERSION >= COMPILER_VS6 && COMPILER_VERSION < COMPILER_VSDOTNET
		#pragma comment(linker, "/OPT:NOWIN98")
	#endif

	#if COMPILER_VERSION >= COMPILER_VSDOTNET
		#define FAST_CALL __declspec(noinline) __fastcall
	#else
		#define FAST_CALL __fastcall
	#endif
#endif

#endif // __ATLIBPLATFORM_H__1305AFF2_6224_47D7_B210_F2A72852FB69
