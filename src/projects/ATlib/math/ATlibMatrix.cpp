/**
 * ATlibMatrix class implementation<br>
 * <b>ATlibMatrix.cpp</b>
 *
 * @author slowhand0309
 */
#include "ATlib/com/ATlibCommon.h"
#include "ATlib/math/ATlibMatrix.h"

// Constructor.
// initialize with default value.
//
// 1 0 0 0
// 0 1 0 0
// 0 0 1 0
// 0 0 0 1
//
ATMatrix::ATMatrix()
{
  clear();
}

// Constructor with value.
ATMatrix::ATMatrix(
  float m11, float m12, float m13, float m14,
  float m21, float m22, float m23, float m24,
  float m31, float m32, float m33, float m34,
  float m41, float m42, float m43, float m44)
{
  set(
    m11, m12, m13, m14,
    m21, m22, m23, m24,
    m31, m32, m33, m34,
    m41, m42, m43, m44
  );
}

// Copy constructor.
ATMatrix::ATMatrix(const ATMatrix &obj)
{
  memcpy(m, obj.m, sizeof(float) * 16);
}

// Destructor.
ATMatrix::~ATMatrix()
{
}

// Operator= .
ATMatrix &ATMatrix::operator=(const ATMatrix &obj)
{
  memcpy(m, obj.m, sizeof(float) * 16);
  return *this;
}

// Operator== .
bool ATMatrix::operator==(const ATMatrix &obj)
{
  return memcmp(m, obj.m, sizeof(float) * 16) == 0;
}

// Operator!= .
bool ATMatrix::operator!=(const ATMatrix &obj)
{
  return !(*this == obj);
}

// Operator[] .
float ATMatrix::operator[](int index)
{
  ATASSERT(index > -1 && index < 17);
  return m[index];
}

// Set default value.
//
// 1 0 0 0
// 0 1 0 0
// 0 0 1 0
// 0 0 0 1
//
void ATMatrix::clear()
{
  set(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

// Set values.
void ATMatrix::set(
  float m11, float m12, float m13, float m14,
  float m21, float m22, float m23, float m24,
  float m31, float m32, float m33, float m34,
  float m41, float m42, float m43, float m44)
{
  m[0] = m11; m[1] = m12; m[2] = m13; m[3] = m14;
  m[4] = m21; m[5] = m22; m[6] = m23; m[7] = m24;
  m[8] = m31; m[9] = m32; m[10] = m33; m[11] = m34;
  m[12] = m41; m[13] = m42; m[14] = m43; m[15] = m44;
}
