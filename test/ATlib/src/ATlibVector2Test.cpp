#include <gtest/gtest.h>
#include "ATlib/math/ATlibVector2.h"

/**
 * ATVector2 Test
 */

TEST(ATVector2, Constructor)
{
   ATVector2 vec2;
   ASSERT_EQ(0, vec2[0]);
   ASSERT_EQ(0, vec2[1]);

   ATVector2 vec22(9.0f, 4.0f);
   ASSERT_EQ(9.0f, vec22[0]);
   ASSERT_EQ(4.0f, vec22[1]);
}

TEST(ATVector2, operator_equal)
{
   ATVector2 fromVec2(5.0f, 10.0f);
   ATVector2 toVec22 = fromVec2;
   ASSERT_EQ(5.0f, toVec22[0]);
   ASSERT_EQ(10.0f, toVec22[1]);
}

TEST(ATVector2, operator_plus)
{
   ATVector2 fromVec2(3.0f, 4.0f);
   ATVector2 toVec22(2.0f, 7.0f);
   toVec22 += fromVec2;
   ASSERT_EQ(5.0f, toVec22[0]);
   ASSERT_EQ(11.0f, toVec22[1]);
}

TEST(ATVector2, comparison)
{
   ATVector2 fromVec2(3.0f, 4.0f);
   ATVector2 toVec22(2.0f, 7.0f);
   ATVector2 toVec23(2.0f, 7.0f);

   ASSERT_EQ(false, toVec22 == fromVec2);
   ASSERT_EQ(true, toVec22 != fromVec2);
   ASSERT_EQ(true, toVec22 == toVec23);
}
