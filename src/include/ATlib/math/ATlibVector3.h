#ifndef __ATLIBVECTOR3_H__
#define __ATLIBVECTOR3_H__

class ATVector3
{
public:
  // Constructor.
  ATVector3();

  // Constructor with initiale value.
  ATVector3(float _x, float _y, float _z);

  // Destructor.
  virtual ~ATVector3();

  // Operator = .
  ATVector3& operator=(const ATVector3& obj);

  // Operator += .
  ATVector3& operator+=(const ATVector3& obj);

  // Operator == .
  bool operator==(const ATVector3& obj);

  // Operator != .
  bool operator!=(const ATVector3& obj);

  // Operator [] .
  float operator[](int index);
private:
  float x;
  float y;
  float z;
};

#endif // __ATLIBVECTOR3_H__
