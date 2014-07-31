#pragma once

/**
 * Vector class for two dimensional use.
 */
class Vector2
{
public:
  // Convenience zero vector
  static const Vector2 ZERO;
  // Convenience unit vector for x axis
  static const Vector2 UNIT_X;
  // Convenience unit vector for y axis
  static const Vector2 UNIT_Y;

  /**
   * Returns a normalized copy of the vector.
   */
  static Vector2 normalize(const Vector2& vec);

  float x;
  float y;

  // Constructors
  Vector2();
  Vector2(float _x, float _y);
  Vector2(const Vector2& copy);
  Vector2& operator=(const Vector2& rhs);

  /**
   * Returns the length/magnitude of the vector.
   */
  float length() const;

  /**
   * Returns the distance to another vector.
   */
  float distance(const Vector2& other) const;

  /**
   * Returns the dot product (scalar product) of this vector with another 
   * vector.
   */
  float dotProd(const Vector2& other) const;

  /**
   * Normalizes the vector into a unit vector.
   */
  void normalize();

  // comparisons
  bool operator==(const Vector2& rhs) const;
  bool operator!=(const Vector2& rhs) const;
  bool operator<(const Vector2& rhs) const;
  bool operator<=(const Vector2& rhs) const;
  bool operator>(const Vector2& rhs) const;
  bool operator>=(const Vector2& rhs) const;

  // add two vectors
  Vector2 operator+(const Vector2& rhs) const;
  // subtract two vectors
  Vector2 operator-(const Vector2& rhs) const;
  // vector scalar multiplication
  Vector2 operator*(const float rhs) const;
  // vector scalar division
  Vector2 operator/(const float rhs) const;
  // negation
  Vector2 operator-() const;
  // add two vectors
  Vector2& operator+=(const Vector2& rhs);
  // subtract two vectors
  Vector2& operator-=(const Vector2& rhs);
  // vector scalar multiplication
  Vector2& operator*=(const float rhs);
  // vector scalar divison
  Vector2& operator/=(const float rhs);
};