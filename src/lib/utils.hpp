#ifndef UTILS_HPP
#define UTILS_HPP

#include <iomanip> // setprecision
#include <sstream>
#include <limits>

template <typename T> std::string NumberToString(T Number, int precision = -1)
{
  std::ostringstream ss;
  if (precision != -1) ss << fixed << setprecision(precision);
  ss << Number;
  return ss.str();
}

float floatApprox(float num, int precision)
{
  const float precisionMul = pow(10, precision);
  const int N              = num * precisionMul;
  return (N - (N % 1)) / precisionMul;
}

bool custom_isnan(double var)
{
    volatile double d = var;
    return d != d;
}
// const float NaN = std::numeric_limits<float>::quiet_NaN();

#endif