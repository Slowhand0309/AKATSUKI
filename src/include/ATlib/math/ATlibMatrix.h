#ifndef __ATLIBMATRIX_H__
#define __ATLIBMATRIX_H__

class ATMatrix
{
public:
  // Constructor.
  ATMatrix();

  // Constructor with value.
  ATMatrix(float m11, float m12, float m13, float m14,
           float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34,
           float m41, float m42, float m43, float m44);

  // Copy constructor.
  ATMatrix(const ATMatrix &obj);

  // Destructor.
  virtual ~ATMatrix();

  // Operator= .
  ATMatrix &operator=(const ATMatrix &obj);

  // Operator== .
  bool operator==(const ATMatrix &obj);

  // Operator!= .
  bool operator!=(const ATMatrix &obj);

  // Operator[] .
  float operator[](int index);

  // Set default value.
  void clear();

  // Set values.
  void set(float m11, float m12, float m13, float m14,
           float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34,
           float m41, float m42, float m43, float m44);

private:
  float m[16];
};
#endif // __ATLIBMATRIX_H__
