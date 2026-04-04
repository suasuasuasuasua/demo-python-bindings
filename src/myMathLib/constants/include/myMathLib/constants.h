#pragma once

#ifdef _WIN32
#ifdef CONSTANTS_EXPORTS
#define CONSTANTS_API __declspec(dllexport)
#else
#define CONSTANTS_API __declspec(dllimport)
#endif
#else
#define CONSTANTS_API __attribute__((visibility("default")))
#endif

namespace myMathLib::constants {

CONSTANTS_API double pi();
CONSTANTS_API double e();
CONSTANTS_API double sqrt2();
CONSTANTS_API double golden_ratio();

}  // namespace myMathLib::constants
