#pragma once

#include <type_traits>
#include <cmath>

/**
 * Compares two floating by checking if they are within a certain margin of 
 * error (defined by epsilon) of each other. Avoids issues with inaccurate 
 * comparisons due to floating point error.
 */
template<typename T>
bool fp_compare(T lhs, T rhs)
{
  static_assert(std::is_floating_point<T>::value, 
                "fp_compare is only for floating point types");
  static const T epsilon = T(1e-8);
  return std::fabs(lhs - rhs) < epsilon;
}