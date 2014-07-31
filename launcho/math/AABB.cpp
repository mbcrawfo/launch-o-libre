#include "math/AABB.h"

#include <cmath>

AABB::AABB()
  : AABB(Vector2::ZERO, Vector2::ZERO)
{}

AABB::AABB(const Vector2& _center, const Vector2& _halfSize)
  : center(_center), halfSize(_halfSize)
{}

AABB::AABB(const Vector2& _center, float sideLength)
  : AABB(_center, Vector2(sideLength / 2.0f, sideLength / 2.0f))
{}

AABB::AABB(const AABB& copy)
  : AABB(copy.center, copy.halfSize)
{}

AABB& AABB::operator=(const AABB& rhs)
{
  center = rhs.center;
  halfSize = rhs.halfSize;
  return *this;
}

bool AABB::contains(const Vector2& pt) const
{
  Vector2 distance(center - pt);
  return (std::fabs(distance.x) <= halfSize.x) && 
         (std::fabs(distance.y) <= halfSize.y);
}

bool AABB::intersect(const AABB& aabb) const
{
  Vector2 distance(aabb.center - center);
  Vector2 size(aabb.halfSize + halfSize);
  distance = Vector2(std::fabs(distance.x), std::fabs(distance.y));  
  size -= distance;
  return (size.x > 0.0f) && (size.y > 0.0f);
}

float AABB::width() const
{
  return halfSize.x * 2.0f;
}

float AABB::height() const
{
  return halfSize.y * 2.0f;
}

float AABB::area() const
{
  return width() * height();
}

float AABB::perimeter() const
{
  return (width() + height()) * 2.0f;
}
