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
  : x(0.0f)
  , y(0.0f)
{
}

/**
 * Constructor.
 *
 * @param _x coodinate x
 * @param _y coodinate y
 */
ATVector2::ATVector2(float _x, float _y)
  : x(_x)
  , y(_y)
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
  x = obj.x;
  y = obj.y;
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
  x += obj.x;
  y += obj.y;
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
  if (x != obj.x) {
    return false;
  }
  if (y != obj.y) {
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
 * [0]: x-coodinate, [1]: y-coodinate
 *
 * @param  index
 * @return value
 */
float ATVector2::operator[](int index)
{
  ATASSERT(index >= 0 && index <= 1);
  if (index == 0) {
    return x;
  } else {
    return y;
  }
}
