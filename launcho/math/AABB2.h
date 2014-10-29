#pragma once

#include "math/Vector2.h"

/**
 * Axis aligned bounding box
 */
class AABB2
{
public:
  // center of the box (pretend vector is a point)
  Vector2 center;
  // width is 2*x component, height is 2*y component
  Vector2 halfSize;

  // constructors
  AABB2();
  AABB2(const float x, const float y, const float _width, const float _height);
  AABB2(const Vector2& _center, const float _width, const float _height);
  AABB2(const Vector2& _center, const Vector2& _halfSize);
  AABB2(const Vector2& _center, float sideLength);
  AABB2(const AABB2& copy);
  AABB2& operator=(const AABB2& rhs);

  /**
   * Using vector as a point, checks if the point is in this box.
   */
  bool contains(const Vector2& pt) const;

  /**
   * Checks if these boxes have an intersection.
   */
  bool intersect(const AABB2& other) const;

  // box information
  float width() const;
  float height() const;
  float area() const;
  float perimeter() const;

  /**
   * Returns the lower left corner of the box.
   */
  Vector2 lowerLeft() const;

  /** 
   * Returns the upper right corner of the box.
   */
  Vector2 upperRight() const;
};