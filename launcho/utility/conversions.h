#pragma once

#include <sstream>

/**
* @return The string representation of val, provided that it implements
* operator<<.
*/
template<typename T>
std::string toString(const T& val)
{
  std::ostringstream ss;
  ss << val;
  return ss.str();
}

template<typename T>
T fromString(const std::string& s)
{
  std::stringstream ss;
  T val;
  ss << s;  
  ss >> val;
  return val;
}