#include "math/Vector2.h"

#include <cassert>
#include "math/fp_compare.h"

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);

Vector2 Vector2::normalize(const Vector2& vec)
{
  Vector2 result = vec;
  result.normalize();
  return result;
}

Vector2::Vector2()
  : Vector2(ZERO)
{}

Vector2::Vector2(float _x, float _y)
  : x(_x), y(_y)
{}

Vector2::Vector2(const Vector2& copy)
  : Vector2(copy.x, copy.y)
{}

Vector2& Vector2::operator=(const Vector2& rhs)
{
  x = rhs.x;
  y = rhs.y;
  return *this;
}

float Vector2::length() const
{
  return std::sqrt((x * x) + (y * y));
}

float Vector2::distance(const Vector2& other) const
{
  return (*this - other).length();
}

float Vector2::dotProd(const Vector2& other) const
{
  return (x * other.x) + (y * other.y);
}

void Vector2::normalize()
{
  float len = length();
  if (fp_compare(len, 0.0f))
  {
    x /= len;
    y /= len;
  }
}

bool Vector2::operator==(const Vector2& rhs) const
{
  return fp_compare(x, rhs.x) && fp_compare(y, rhs.y);
}

bool Vector2::operator!=(const Vector2& rhs) const
{
  return !(*this == rhs);
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
  return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
  return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(const float rhs) const
{
  return Vector2(x * rhs, y * rhs);
}

Vector2 Vector2::operator/(const float rhs) const
{
  assert(!fp_compare(rhs, 0.0f));
  return Vector2(x / rhs, y / rhs);
}

Vector2 Vector2::operator-() const
{
  return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
  *this = *this + rhs;
  return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
  *this = *this - rhs;
  return *this;
}

Vector2& Vector2::operator*=(const float rhs)
{
  *this = *this * rhs;
  return *this;
}

Vector2& Vector2::operator/=(const float rhs)
{
  *this = *this / rhs;
  return *this;
}
