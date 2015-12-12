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
