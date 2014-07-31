#pragma once

#include "math/Vector2.h"

/**
 * Axis aligned bounding box
 */
class AABB
{
public:
  // center of the box (pretend vector is a point)
  Vector2 center;
  // width is 2*x component, height is 2*y component
  Vector2 halfSize;

  // constructors
  AABB();
  AABB(const Vector2& _center, const Vector2& _halfSize);
  AABB(const Vector2& _center, float sideLength);
  AABB(const AABB& copy);
  AABB& operator=(const AABB& rhs);

  /**
   * Using vector as a point, checks if the point is in this box.
   */
  bool contains(const Vector2& pt) const;

  /**
   * Checks if these boxes have an intersection.
   */
  bool intersect(const AABB& aabb) const;

  // box information
  float width() const;
  float height() const;
  float area() const;
  float perimeter() const;
};