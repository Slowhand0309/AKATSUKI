#ifndef __ATLIBVECTOR4_H__
#define __ATLIBVECTOR4_H__

class ATVector4
{
public:
  // Constructor.
  ATVector4();

  // Constructor with initiale value.
  ATVector4(float _x, float _y, float _z, float _w);

  // Destructor.
  virtual ~ATVector4();

  // Operator = .
  ATVector4& operator=(const ATVector4& obj);

  // Operator += .
  ATVector4& operator+=(const ATVector4& obj);

  // Operator == .
  bool operator==(const ATVector4& obj);

  // Operator != .
  bool operator!=(const ATVector4& obj);

  // Operator [] .
  float operator[](int index);
private:
  float x;
  float y;
  float z;
  float w;
};

#endif // __ATLIBVECTOR4_H__
