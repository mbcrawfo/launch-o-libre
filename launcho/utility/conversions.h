#pragma once

#include "math/Vector2.h"
#include <SFML/System/Vector2.hpp>
#include <sstream>

/**
* Returns the string representation of val, provided that it implements
* operator<<.
*/
template<typename T>
std::string toString(const T& val)
{
  std::ostringstream ss;
  ss << val;
  return ss.str();
}

/**
 * Attempts to convert the string to the given type.
 */
template<typename T>
T fromString(const std::string& s)
{
  std::stringstream ss;
  T val;
  ss << s;  
  ss >> val;
  return val;
}

inline Vector2 convert(const sf::Vector2f& v)
{
  return Vector2(v.x, v.y);
}

inline sf::Vector2f convert(const Vector2& v)
{
  return sf::Vector2f(v.x, v.y);
}