#include <gtest/gtest.h>
#include "ATlib/utl/ATlibDateUtl.h"

#define TEST_FORMAT _T("%Y/%m/%d")

/**
 * ATDateUtl Test
 */

TEST(ATDateUtlTest, getCurrentDate)
{
    ASSERT_EQ(false, ATStringUtl::isEmpty(ATDateUtl::getCurrentDate()));
}

TEST(ATDateUtlTest, getCurrentDateFormat)
{
    ASSERT_EQ(false, ATStringUtl::isEmpty(ATDateUtl::getCurrentDate(TEST_FORMAT)));
}
