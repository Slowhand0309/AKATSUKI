#include <unistd.h>
#include "ATlib/utl/ATlibSysUtl.h"

#if defined(PLATFORM_MACOS) || defined(PLATFORM_IOS)
#include <mach-o/dyld.h>
#include <libgen.h>
#endif

/**
 * Get module name
 *
 * @return TString     moduel name
 */
TString ATSysUtl::getModuleName() {

  TString		strRet = _T("");
  TCHAR	szFullPath[_MAX_PATH] = {0};
  TCHAR	szFname[_MAX_FNAME] = {0};

#if defined(PLATFORM_WINDOWS)
  // Windows
  // get full path for module
  GetModuleFileName(GetModuleHandle(NULL), szFullPath, _MAX_PATH);

  // split path
  _tsplitpath_s(szFullPath, NULL, 0, NULL, 0, szFname, _MAX_FNAME, NULL, 0);
#endif // PLATFORM_WINDOWS

#if defined(PLATFORM_MACOS) || defined(PLATFORM_IOS)
  // Mac OS
  char buff[_MAX_FNAME] = {0};
  uint32_t size = sizeof(buff);

  // Get module full path.
  _NSGetExecutablePath(buff, &size);
  char *szTemp = basename(buff);
#if defined(UNICODE) || defined(_UNICODE)
  ATStringUtl::multi2Wide(szTemp, szFname, _MAX_FNAME);
#else
  strcpy(szFname, szTemp);
#endif // UNICODE
#endif // PLATFORM_MACOS || PLATFORM_IOS

#if defined(PLATFORM_LINUX)
  // Linux
  char buff[_MAX_FNAME] = {0};
  readlink("/proc/self/exe", buff, sizeof(buff));

#if defined(UNICODE) || defined(_UNICODE)
  ATStringUtl::multi2Wide(buff, szFname, _MAX_FNAME);
#else
  strcpy(szFname, buff);
#endif // UNICODE

#endif // PLATFORM_LINUX

  strRet = TString(szFname);
  return strRet;
}

/**
 * Get current path
 *
 * @return TString     path
 */
TString ATSysUtl::getCurrentPath() {

  TCHAR	szFullPath[_MAX_PATH] = {0};
  TCHAR	szDir[_MAX_DIR] = {0};
  TCHAR	szFname[_MAX_FNAME] = {0};
  TCHAR	szExt[_MAX_EXT] = {0};

#ifdef PLATFORM_WINDOWS
  // get full path for module
  GetModuleFileName(GetModuleHandle(NULL), szFullPath, _MAX_PATH);

  // split path
  _tsplitpath_s( szFullPath, NULL, 0, szDir, _MAX_DIR
    , szFname, _MAX_FNAME, szExt, _MAX_EXT );

#else
#if defined(UNICODE) || defined(_UNICODE)
  char buff[_MAX_PATH];
  getcwd(buff, _MAX_PATH);
  ATStringUtl::multi2Wide(buff, szDir, _MAX_FNAME);
#else
  getcwd(szDir, _MAX_PATH);
#endif // UNICODE
#endif // PLATFORM_WINDOWS
  return TString(szDir);
}

/**
 * Get file extension.
 *
 * @param szPath  file path
 * @return TString file extension
 */
TString ATSysUtl::getExtension(const TString &szPath) {

  TString		szExtension = _T("");
  unsigned int uiPoint = 0;

  if(szPath.empty()){
    return _T("");
  }

  while(szPath[uiPoint] != _T('\0')){

    /* split comma */
    if(szPath[uiPoint] == _T('.')){
      break;
    }
    ++uiPoint;

    if(static_cast<unsigned int>(szPath.length()) <= uiPoint){
      /* none */
      return _T("");
    }
  }

  szExtension = szPath.substr(++uiPoint);
  return szExtension;
}

/**
 * check path.
 *
 * @param szPath path for check
 * @return true  : valid
 *         false : unvalid
 */
bool ATSysUtl::hasPath(const TString &szPath) {

  int		iRet = 0;
  struct stat tagStat;

  if(szPath.empty()){
    return false;
  }

  /* check path */
  iRet = _tstat(szPath.c_str(), &tagStat);
  if(iRet != 0){
    if(errno == ENOENT){
      /* enoent */
    } else if(errno == EINVAL){
      /* _tstat error */
    }
    return false;
  }
  return true;
}

ATSysUtl::ATSysUtl() {
}
