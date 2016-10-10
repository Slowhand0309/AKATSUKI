#ifndef __ATLIBVECTOR2_H__
#define __ATLIBVECTOR2_H__


class ATVector2
{
public:
  // Constructor.
  ATVector2();

  // Constructor with initiale value.
  ATVector2(float _x, float _y);

  // Destructor.
  virtual ~ATVector2();

  // Operator = .
  ATVector2& operator=(const ATVector2& obj);

  // Operator += .
  ATVector2& operator+=(const ATVector2& obj);

  // Operator == .
  bool operator==(const ATVector2& obj);

  // Operator != .
  bool operator!=(const ATVector2& obj);

  // Operator [] .
  float operator[](int index);
private:
  float x;
  float y;
};
#endif // __ATLIBVECTOR2_H__
