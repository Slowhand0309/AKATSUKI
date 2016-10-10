/**
 * ATVector3 class implementation<br>
 * <b>ATlibVector3.cpp</b>
 *
 * @author slowhand0309
 */
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/math/ATlibVector3.h"

/**
 * Constructor.
 */
ATVector3::ATVector3()
  : x(0.0f)
  , y(0.0f)
  , z(0.0f)
{
}

/**
 * Constructor.
 *
 * @param _x coodinate x
 * @param _y coodinate y
 * @param _z coodinate z
 */
ATVector3::ATVector3(float _x, float _y, float _z)
  : x(_x)
  , y(_y)
  , z(_z)
{
}

/**
 * Destructor.
 */
ATVector3::~ATVector3()
{
}

/**
 * operator=
 *
 * @param obj
 * @return ATVector3
 */
ATVector3& ATVector3::operator=(const ATVector3& obj)
{
  x = obj.x;
  y = obj.y;
  z = obj.z;
  return *this;
}

/**
 * operator+=
 *
 * @param obj
 * @return ATVector3
 */
ATVector3& ATVector3::operator+=(const ATVector3& obj)
{
  x += obj.x;
  y += obj.y;
  z += obj.z;
  return *this;
}

/**
 * operator==
 *
 * @param obj
 * @return true  : equal
 *         false : not equal
 */
bool ATVector3::operator==(const ATVector3& obj)
{
  if (x != obj.x) {
    return false;
  }
  if (y != obj.y) {
    return false;
  }
  if (z != obj.z) {
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
bool ATVector3::operator!=(const ATVector3& obj)
{
  return !(*this == obj);
}

/**
 * operator[]
 * [0]: x-coodinate, [1]: y-coodinate, [2]: z-coodinate
 *
 * @param  index
 * @return value
 */
float ATVector3::operator[](int index)
{
  ATASSERT(index >= 0 && index <= 2);
  if (index == 0) {
    return x;
  } else if (index == 1){
    return y;
  } else {
    return z;
  }
}
