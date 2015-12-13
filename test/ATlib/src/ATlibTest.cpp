#include <gtest/gtest.h>
#include "ATlib/utl/ATlibStringUtl.h"

/**
 * ATStringUtl Test
 */

TEST(ATStringUtlTest, isEmpty)
{
    ASSERT_EQ(true, ATStringUtl::isEmpty(TString(_T(""))));
}

TEST(ATStringUtlTest, isNotEmpty)
{
    ASSERT_EQ(false, ATStringUtl::isNotEmpty(TString(_T(""))));
}

TEST(ATStringUtlTest, isDigit)
{
    const char digit = '9';
    ASSERT_EQ(true, ATStringUtl::isDigit(digit));

    TString szBuff = _T("12acd45");
    ASSERT_EQ(false, ATStringUtl::isDigit(szBuff));

    TString szBuff2 = _T("9");
    ASSERT_EQ(true, ATStringUtl::isDigit(szBuff2));
}

TEST(ATStringUtlTest, contains)
{
    const TString szValue = _T("abcdefg");
    const TString szAt1 = _T("cd");
    ASSERT_EQ(true, ATStringUtl::contains(szValue, szAt1));

    const TString szAt2 = _T("xyz");
    ASSERT_EQ(false, ATStringUtl::contains(szValue, szAt2));
}

TEST(ATStringUtlTest, split)
{
    const TString szValue = _T("abc,def");
    const TString szDelimiter = _T(",");

    std::list<TString> list = ATStringUtl::split(szValue, szDelimiter);
    ASSERT_EQ(2, list.size());

    const TCHAR *expValues[] = {_T("abc"), _T("def")};

    int index = 0;
    std::list<TString>::iterator it;
    for (it = list.begin(); it != list.end(); it++, index++) {
        printf("%s", (*it).c_str());
        ASSERT_STREQ(expValues[index], (*it).c_str());
    }
}

TEST(ATStringUtlTest, erase)
{
    const TString szValue = _T("abcdef");
    const TString szAt = _T("cd");

    TString ret = ATStringUtl::erase(szValue, szAt);
    ASSERT_STREQ(_T("abef"), ret.c_str());
}
