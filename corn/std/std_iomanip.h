#ifndef STD_IOMANIP_H
#define STD_IOMANIP_H
// This is to allow a common include point for old and new C++ vendor libraries
#include <corn/std/std_check.h>
#ifdef OLD_STD
#     include <iomanip.h>
#else
#     include <iomanip>
#endif
#endif

