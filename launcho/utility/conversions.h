#pragma once

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