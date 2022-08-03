#ifndef CORN_STD_CHECK_H
#define CORN_STD_CHECK_H
// This is to allow a common include point for old and new C++ vendor libraries
#ifdef _MSC_VER
#  if (_MSC_VER<1300)
#     define OLD_STD
#  endif
#endif
#ifdef __BCPLUSPLUS__
#  if (__BCPLUSPLUS__ < 0x0520)
      // BC 5.01 does not have std:: (I.e. for ostream)
      // C++ Builder  (I think version 3 0x0530 and version 4 0x0540 for would also work, but haven't tried them
#     define OLD_STD
#  endif
#endif

// For SunStudio11 and probably most recent Unix compilers have std::
// Probably most recent Linux compilers have std::
#ifdef OLD_STD
#error reached
#  define STD_NS
#else


#  define STD_NS std::
#endif


#ifdef unix
// unix doesn't have, or is already, in binary mode?
#  define OR_IOS_BINARY
#else
// I think this may be DOS/Windows specific, so the ifdef would be if not __MSDOS__
#  define OR_IOS_BINARY   |std:: ios::binary
#endif
#endif

