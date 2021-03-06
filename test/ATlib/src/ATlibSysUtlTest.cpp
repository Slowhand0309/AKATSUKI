#include <gtest/gtest.h>
#include "ATlib/utl/ATlibSysUtl.h"

/**
 * ATSysUtl Test
 */

TEST(ATSysUtlTest, getModuleName)
{
     TString ex = ATSysUtl::getModuleName();
     ASSERT_STREQ(_T("ATlibTest"), ex.c_str());
}


TEST(ATSysUtlTest, getCurrentPath)
{
   TString ex = ATSysUtl::getCurrentPath();
   ASSERT_STRNE(_T(""), ex.c_str());
}


TEST(ATSysUtlTest, getExtension)
{
    TString szPath = _T("/test/src/file.cpp");
    TString ex = ATSysUtl::getExtension(szPath);

    ASSERT_STREQ(_T("cpp"), ex.c_str());
}

TEST(ATSysUtlTest, noHasPath)
{
    TString szPath = _T("/test/src/hoge.cpp");
    bool ret = ATSysUtl::hasPath(szPath);

    ASSERT_EQ(false, ret);
}

TEST(ATSysUtlTest, hasPath)
{
    TString szPath = _T("./build/test/ATlib/ATlibTest");
    bool ret = ATSysUtl::hasPath(szPath);

    ASSERT_EQ(true, ret);
}
