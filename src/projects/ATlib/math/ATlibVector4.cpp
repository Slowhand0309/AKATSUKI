/**
 * ATVector4 class implementation<br>
 * <b>ATlibVector4.cpp</b>
 *
 * @author slowhand0309
 */
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/math/ATlibVector4.h"

/**
 * Constructor.
 */
ATVector4::ATVector4()
  : x(0.0f)
  , y(0.0f)
  , z(0.0f)
  , w(0.0f)
{
}

/**
 * Constructor.
 *
 * @param _x coodinate x
 * @param _y coodinate y
 * @param _z coodinate z
 * @param _w coodinate w
 */
ATVector4::ATVector4(float _x, float _y, float _z, float _w)
  : x(_x)
  , y(_y)
  , z(_z)
  , w(_w)
{
}

/**
 * Destructor.
 */
ATVector4::~ATVector4()
{
}

/**
 * operator=
 *
 * @param obj
 * @return ATVector4
 */
ATVector4& ATVector4::operator=(const ATVector4& obj)
{
  x = obj.x;
  y = obj.y;
  z = obj.z;
  w = obj.w;
  return *this;
}

/**
 * operator+=
 *
 * @param obj
 * @return ATVector4
 */
ATVector4& ATVector4::operator+=(const ATVector4& obj)
{
  x += obj.x;
  y += obj.y;
  z += obj.z;
  w += obj.w;
  return *this;
}

/**
 * operator==
 *
 * @param obj
 * @return true  : equal
 *         false : not equal
 */
bool ATVector4::operator==(const ATVector4& obj)
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
  if (w != obj.w) {
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
bool ATVector4::operator!=(const ATVector4& obj)
{
  return !(*this == obj);
}

/**
 * operator[]
 * [0]: x-coodinate, [1]: y-coodinate, [2]: z-coodinate, [3]: w-coodinate
 *
 * @param  index
 * @return value
 */
float ATVector4::operator[](int index)
{
  ATASSERT(index >= 0 && index <= 3);
  if (index == 0) {
    return x;
  } else if (index == 1){
    return y;
  } else if (index == 2){
    return z;
  } else {
    return w;
  }
}
