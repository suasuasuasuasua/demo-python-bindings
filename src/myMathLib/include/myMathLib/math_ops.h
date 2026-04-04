#pragma once

#ifdef _WIN32
#  ifdef MYMATHLIB_EXPORTS
#    define MYMATHLIB_API __declspec(dllexport)
#  else
#    define MYMATHLIB_API __declspec(dllimport)
#  endif
#else
#  define MYMATHLIB_API __attribute__((visibility("default")))
#endif

namespace myMathLib {

MYMATHLIB_API double add(double a, double b);
MYMATHLIB_API double subtract(double a, double b);
MYMATHLIB_API double multiply(double a, double b);
MYMATHLIB_API double divide(double a, double b);
MYMATHLIB_API double power(double base, double exponent);

} // namespace myMathLib
