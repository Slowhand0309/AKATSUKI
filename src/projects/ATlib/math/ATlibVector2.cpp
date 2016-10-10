/**
 * ATVector2 class implementation<br>
 * <b>ATlibVector2.cpp</b>
 *
 * @author slowhand0309
 */
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/math/ATlibVector2.h"

/**
 * Constructor.
 */
ATVector2::ATVector2()
  : ml_v1(0.0f)
  , ml_v2(0.0f)
{
}

/**
 * Constructor.
 *
 * @param f1 value1
 * @param f2 value2
 */
ATVector2::ATVector2(float f1, float f2)
  : ml_v1(f1)
  , ml_v2(f2)
{
}

/**
 * Destructor.
 */
ATVector2::~ATVector2()
{
}

/**
 * operator=
 *
 * @param obj
 * @return ATVector2
 */
ATVector2& ATVector2::operator=(const ATVector2& obj)
{
  ml_v1 = obj.ml_v1;
  ml_v2 = obj.ml_v2;
  return *this;
}

/**
 * operator+=
 *
 * @param obj
 * @return ATVector2
 */
ATVector2& ATVector2::operator+=(const ATVector2& obj)
{
  ml_v1 += obj.ml_v1;
  ml_v2 += obj.ml_v2;
  return *this;
}

/**
 * operator==
 *
 * @param obj
 * @return true  : equal
 *         false : not equal
 */
bool ATVector2::operator==(const ATVector2& obj)
{
  if (ml_v1 != obj.ml_v1) {
    return false;
  }
  if (ml_v2 != obj.ml_v2) {
    return false;
  }
  return true;
}

/**
 * operator!=
 *
 * @param obj
 * @return false : equal
 *         true  : not equal
 */
bool ATVector2::operator!=(const ATVector2& obj)
{
  return !(*this == obj);
}

/**
 * operator[]
 *
 * @param  index
 * @return value
 */
float ATVector2::operator[](int index)
{
  ATASSERT(index >= 0 && index <= 1);
  if (index == 0) {
    return ml_v1;
  } else {
    return ml_v2;
  }
}
