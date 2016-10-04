#include <unistd.h>
#include "ATlib/utl/ATlibSysUtl.h"

/**
 * Get module name
 *
 * @return TString     moduel name
 */
TString ATSysUtl::getModuleName() {

  TString		strRet = _T("");
  TCHAR	szFullPath[_MAX_PATH] = {0};
  TCHAR	szFname[_MAX_FNAME] = {0};

#ifdef PLATFORM_WINDOWS
  // get full path for module
  GetModuleFileName(GetModuleHandle(NULL), szFullPath, _MAX_PATH);

  // split path
  _tsplitpath_s(szFullPath, NULL, 0, NULL, 0, szFname, _MAX_FNAME, NULL, 0);
#else

#if defined(UNICODE) || defined(_UNICODE)
  char buff[_MAX_FNAME] = {0};
  readlink("/proc/self/exe", buff, sizeof(buff));
  ATStringUtl::multi2Wide(buff, szFname, _MAX_FNAME);
#else
  readlink("/proc/self/exe", szFname, sizeof(szFname));
#endif // UNICODE

#endif // PLATFORM_WINDOWS

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
  ATStringUtl::multi2Wide(buff, szFname, _MAX_FNAME);
#else
  getcwd(szFname, _MAX_PATH);
#endif // UNICODE
#endif // PLATFORM_WINDOWS
  return TString(szDir);
}

/**
 * Get file extension.
 *
 * @param const TString &szPath  file path
 * @return TString file extension
 */
TString ATSysUtl::getExtension(const TString &szPath) {

  TString		szExtension = _T("");
  unsigned int uiPoint = 0;

  if(szPath.empty()){
    return _T("");
  }

  unsigned int uiStrLen = szPath.length();
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
 * @param const TString &szPath path for check
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
