#ifndef STD_FSTREAM_H
#define STD_FSTREAM_H

// This is to allow a common include point for old and new C++ vendor libraries
#include <corn/std/std_check.h>
#ifdef OLD_STD
#     include <fstream.h>
#else
#     include <fstream>
#endif
/*100826
#ifdef NEW_STD
#  if (__BCPLUSPLUS__ == 0x0550)
      // BC++ 5.0 still didn't have fstream
#     include <fstream.h>
#  else
#     include <fstream>
#  endif
//091122      using namespace std;
#else
#     include <fstream.h>
#endif
*/
#endif

