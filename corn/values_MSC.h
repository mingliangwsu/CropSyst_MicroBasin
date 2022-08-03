#ifndef VALUES_MSC_H
#define VALUES_MSC_H

// For some stupid reason MicroSoft does not provided the values.h
// that every other compiler vendor provides.

#include <limits.h>
#include <float.h>

#     define MAXFLOAT    FLT_MAX
#     define MINFLOAT    FLT_MIN
#ifndef MAXSHORT
#     define MAXSHORT    SHRT_MAX
#endif
#ifndef MAXLONG
#     define MAXLONG     LONG_MAX
#endif

#endif