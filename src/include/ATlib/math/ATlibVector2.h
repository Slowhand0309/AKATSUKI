#ifndef __ATLIBLOGGER_H__
#define __ATLIBLOGGER_H__


class ATVector2
{
public:
  // Constructor.
  ATVector2();

  // Constructor with initiale value.
  ATVector2(float f1, float f2);

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
  float ml_v1;
  float ml_v2;
};
#endif // __ATLIBLOGGER_H__
