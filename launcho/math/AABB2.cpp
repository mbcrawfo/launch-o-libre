#include "math/AABB2.h"

#include <cmath>

AABB2::AABB2()
  : AABB2(Vector2::ZERO, Vector2::ZERO)
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

bool AABB2::intersect(const AABB2& aabb) const
{
  Vector2 distance(aabb.center - center);
  Vector2 size(aabb.halfSize + halfSize);
  distance = Vector2(std::fabs(distance.x), std::fabs(distance.y));  
  size -= distance;
  return (size.x > 0.0f) && (size.y > 0.0f);
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
