#include "math/AABB2.h"

#include <cmath>

AABB2::AABB2()
  : AABB2(Vector2::ZERO, Vector2::ZERO)
{}

AABB2::AABB2(const float x, const float y, const float _width,
             const float _height)
  : AABB2(Vector2(x, y), Vector2(_width / 2.0f, _height / 2.0f))
{}

AABB2::AABB2(const Vector2& _center, const float _width, const float _height)
  : AABB2(_center, Vector2(_width / 2.0f, _height / 2.0f))
{}

AABB2::AABB2(const Vector2& _center, const Vector2& _halfSize)
  : center(_center), halfSize(_halfSize)
{}

AABB2::AABB2(const Vector2& _center, float sideLength)
  : AABB2(_center, Vector2(sideLength / 2.0f, sideLength / 2.0f))
{}

AABB2::AABB2(const AABB2& copy)
  : AABB2(copy.center, copy.halfSize)
{}

AABB2& AABB2::operator=(const AABB2& rhs)
{
  center = rhs.center;
  halfSize = rhs.halfSize;
  return *this;
}

bool AABB2::contains(const Vector2& pt) const
{
  Vector2 distance(center - pt);
  return (std::fabs(distance.x) <= halfSize.x) && 
         (std::fabs(distance.y) <= halfSize.y);
}

bool AABB2::intersect(const AABB2& other) const
{
  Vector2 myDim = center + (halfSize * 2.0f);
  Vector2 otherDim = other.center + (other.halfSize * 2.0f);
  return (center <= otherDim) && (other.center <= myDim);
}

float AABB2::width() const
{
  return halfSize.x * 2.0f;
}

float AABB2::height() const
{
  return halfSize.y * 2.0f;
}

float AABB2::area() const
{
  return width() * height();
}

float AABB2::perimeter() const
{
  return (width() + height()) * 2.0f;
}

Vector2 AABB2::min() const
{
  return center - halfSize;
}

Vector2 AABB2::max() const
{
  return center + halfSize;
}
